
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicBoolean;

public class ThreadedGraphColoring {
    public static int[] colorGraph(Graph graph, int colors, int maxThreads) throws InterruptedException {
        int nodes = graph.getNodesNumber();
        int[] nodeColors = new int[nodes];
        Arrays.fill(nodeColors, -1); // Initialize node colors with -1

        AtomicBoolean solutionFound = new AtomicBoolean(false);
        CountDownLatch latch = new CountDownLatch(1); // Synchronize when solution is found

        ExecutorService executor = Executors.newFixedThreadPool(maxThreads);

        try {
            executor.submit(() -> solve(graph, colors, 0, nodeColors, solutionFound, latch));
            if(!latch.await(1, TimeUnit.MINUTES)) {
                throw new RuntimeException("Timeout waiting for threads to finish");
            } // Wait for the solution to be found
        } finally {
            executor.shutdown();
        }

        if (solutionFound.get()) {
            return nodeColors;
        } else {
            throw new IllegalStateException("No valid coloring found");
        }
    }

    private static void solve(Graph graph, int colors, int currentNode, int[] nodeColors,
                              AtomicBoolean solutionFound, CountDownLatch latch) {
        if (solutionFound.get()) {
            return; // Exit if solution is found
        }

        if (currentNode == graph.getNodesNumber()) {
            solutionFound.set(true);
            latch.countDown(); // Mark solution found
            return;
        }

        for (int color = 0; color < colors; color++) {
            if (isValidColor(graph, currentNode, color, nodeColors)) {
                nodeColors[currentNode] = color;

                // Start the next node coloring in a new thread
                Thread nextTask = new Thread(() -> solve(graph, colors, currentNode + 1, nodeColors, solutionFound, latch));
                nextTask.start();

                try {
                    nextTask.join(); // Ensure the thread completes before continuing
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }

                if (solutionFound.get()) {
                    return; // Exit if a solution has been found
                }

                nodeColors[currentNode] = -1; // Backtrack if no solution found for this color
            }
        }
    }

    private static boolean isValidColor(Graph graph, int node, int color, int[] nodeColors) {
        for (int neighbor : graph.getNeighbors(node)) {
            if (nodeColors[neighbor] == color) {
                return false; // Conflict with neighboring node's color
            }
        }
        return true;
    }
}

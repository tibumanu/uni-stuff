package Threads;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicBoolean;

public class ThreadedGraphColoring {
    public static int[] colorGraph(Graph graph, int colors, int maxThreads) throws InterruptedException {
        int nodes = graph.getNodesNumber();
        int[] nodeColors = new int[nodes];
        Arrays.fill(nodeColors, -1);

        AtomicBoolean solutionFound = new AtomicBoolean(false);
        CountDownLatch latch = new CountDownLatch(1); // synchronization

        ExecutorService executor = Executors.newFixedThreadPool(maxThreads);

        try {
            executor.submit(() -> solve(graph, colors, 0, nodeColors, solutionFound, latch));
            if(!latch.await(1, TimeUnit.MINUTES)) {
                throw new RuntimeException("Timeout waiting for threads to finish");
            }
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
            return; // solution found
        }

        if (currentNode == graph.getNodesNumber()) {
            solutionFound.set(true);
            latch.countDown(); // solution found
            return;
        }

        boolean colorAssigned = false;

        for (int color = 0; color < colors; color++) {
            if (isValidColor(graph, currentNode, color, nodeColors)) {
                nodeColors[currentNode] = color;
                colorAssigned = true;

                // new thread
                if (!solutionFound.get()) {
                    Thread nextTask = new Thread(() -> solve(graph, colors, currentNode + 1, nodeColors, solutionFound, latch));
                    nextTask.start();
                    try {
                        nextTask.join();
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                    }
                }

                if (solutionFound.get()) {
                    return;
                }

                nodeColors[currentNode] = -1;
            }
        }

        if (!colorAssigned) {
            return;
        }
    }

    private static boolean isValidColor(Graph graph, int node, int color, int[] nodeColors) {
        for (int neighbor : graph.getNeighbors(node)) {
            if (nodeColors[neighbor] == color) {
                return false; // conflict with neighbor
            }
        }
        return true;
    }
}

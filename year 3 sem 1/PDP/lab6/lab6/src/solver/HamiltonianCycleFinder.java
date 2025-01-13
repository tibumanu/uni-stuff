package solver;
import model.Graph;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class HamiltonianCycleFinder {
    private final Graph graph;
    private volatile boolean cycleFound = false;
    private final List<Integer> resultPath = new ArrayList<>();
    private final ExecutorService executor;

    public HamiltonianCycleFinder(Graph graph) {
        this.graph = graph;
        int numNodes = graph.getNodes().size();
        executor = Executors.newFixedThreadPool(numNodes);
    }

    public List<Integer> findHamiltonianCycle() throws InterruptedException {
        Set<Integer> nodes = graph.getNodes();
        if (nodes.isEmpty()) return null;

        int startNode = nodes.iterator().next();
        List<Integer> path = new ArrayList<>();
        path.add(startNode);

        List<Future<?>> futures = new ArrayList<>();
        for (int neighbor : graph.getNeighbors(startNode)) {
            futures.add(executor.submit(() -> search(neighbor, path, nodes.size(), startNode)));
        }

        for (Future<?> future : futures) {
            try {
                future.get();
            } catch (ExecutionException e) {
                e.printStackTrace();
            }
        }

        executor.shutdown();
        return cycleFound ? resultPath : null;
    }

    // backtrack
    private void search(int current, List<Integer> path, int totalNodes, int startNode) {
        if (cycleFound) return;

        path.add(current);

        if (path.size() == totalNodes) {
            if (graph.hasEdge(current, startNode)) {
                synchronized (this) {
                    if (!cycleFound) {
                        cycleFound = true;
                        resultPath.clear();
                        resultPath.addAll(path);
                    }
                }
            }
            path.remove(path.size() - 1);
            return;
        }

        for (int neighbor : graph.getNeighbors(current)) {
            if (!path.contains(neighbor)) {
                search(neighbor, new ArrayList<>(path), totalNodes, startNode);
            }
        }

        path.remove(path.size() - 1);
    }
}

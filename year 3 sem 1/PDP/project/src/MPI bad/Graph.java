package MPI;
import java.util.*;

public class Graph {
    private Map<Integer, Set<Integer>> adjacencyList = new HashMap<>();

    public Graph(int nodes) {
        adjacencyList = new HashMap<>();
        for (int i = 0; i < nodes; i++) {
            adjacencyList.put(i, new HashSet<>());
        }
    }


    public void setAdjacencyList(Map<Integer, Set<Integer>> adjacencyList) {
        this.adjacencyList = adjacencyList;
    }
    public void addNode(int node) {
        adjacencyList.putIfAbsent(node, new HashSet<>());
    }

    public void addEdge(int from, int to) {
        adjacencyList.putIfAbsent(from, new HashSet<>());
        adjacencyList.putIfAbsent(to, new HashSet<>());
        adjacencyList.get(from).add(to);
        adjacencyList.get(to).add(from);
    }

    public Set<Integer> getNeighbors(int node) {
        return adjacencyList.getOrDefault(node, Collections.emptySet());
    }

    public boolean hasEdge(int from, int to) {
        return adjacencyList.getOrDefault(from, Collections.emptySet()).contains(to);
    }

    public Set<Integer> getNodes() {
        return adjacencyList.keySet();
    }

    public int getNodesNumber() {
        return adjacencyList.size();
    }

    public static Graph generateRandomGraph(int numNodes, int numEdges) {
        Graph graph = new Graph(numNodes);
        Random random = new Random();

        for (int i = 0; i < numNodes; i++) {
            graph.addNode(i);
        }

        int edgeCount = 0;
        while (edgeCount < numEdges) {
            int from = random.nextInt(numNodes);
            int to = random.nextInt(numNodes);
            if (from != to && !graph.hasEdge(from, to)) {
                graph.addEdge(from, to);
                edgeCount++;
            }
        }

        return graph;
    }

    public static Graph generateRandomGraphWithEdgeForEachNode(int numNodes, int numEdges) {
        Graph graph = new Graph(numNodes);
        Random random = new Random();

        for (int i = 0; i < numNodes; i++) {
            graph.addNode(i);
        }

        for (int i = 0; i < numNodes - 1; i++) {
            graph.addEdge(i, i + 1);
        }
        graph.addEdge(numNodes - 1, 0);

        int currentEdgeCount = numNodes;
        while (currentEdgeCount < numEdges) {
            int from = random.nextInt(numNodes);
            int to = random.nextInt(numNodes);
            if (from != to && !graph.getNeighbors(from).contains(to)) {
                graph.addEdge(from, to);
                currentEdgeCount++;
            }
        }

        return graph;
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        for (int node : adjacencyList.keySet()) {
            builder.append(node).append(" -> ").append(adjacencyList.get(node)).append("\n");
        }
        return builder.toString();
    }
}

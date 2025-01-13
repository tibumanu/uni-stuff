package model;
import java.util.*;

public class Graph {
    private final Map<Integer, List<Integer>> adjacencyList = new HashMap<>();

    public void addNode(int node) {
        adjacencyList.putIfAbsent(node, new ArrayList<>());
    }

    public void addEdge(int from, int to) {
        adjacencyList.putIfAbsent(from, new ArrayList<>());
        adjacencyList.putIfAbsent(to, new ArrayList<>());
        adjacencyList.get(from).add(to);
    }

    public List<Integer> getNeighbors(int node) {
        return adjacencyList.getOrDefault(node, Collections.emptyList());
    }

    public boolean hasEdge(int from, int to) {
        return adjacencyList.getOrDefault(from, Collections.emptyList()).contains(to);
    }

    public Set<Integer> getNodes() {
        return adjacencyList.keySet();
    }

    public static Graph generateRandomGraph(int numNodes, int numEdges) {
        Graph graph = new Graph();
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

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        for (int node : adjacencyList.keySet()) {
            builder.append(node).append(" → ").append(adjacencyList.get(node)).append("\n");
        }
        return builder.toString();
    }
}

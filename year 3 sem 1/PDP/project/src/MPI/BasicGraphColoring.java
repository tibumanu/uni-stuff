

import java.util.Arrays;

public class BasicGraphColoring {
    public static int[] colorGraph(Graph graph, int colors) {
        int nodes = graph.getNodesNumber();
        int[] nodeColors = new int[nodes];
        Arrays.fill(nodeColors, -1); // Initialize all nodes as uncolored

        if (colorGraphBacktracking(graph, colors, nodeColors, 0)) {
            return nodeColors; // Successfully colored
        } else {
            throw new IllegalStateException("No valid coloring found with " + colors + " colors");
        }
    }

    private static boolean colorGraphBacktracking(Graph graph, int colors, int[] nodeColors, int currentNode) {
        if (currentNode == graph.getNodesNumber()) {
            return true; // All nodes have been successfully colored
        }

        for (int color = 0; color < colors; color++) {
            if (isValidColor(graph, currentNode, color, nodeColors)) {
                nodeColors[currentNode] = color; // Assign color
                if (colorGraphBacktracking(graph, colors, nodeColors, currentNode + 1)) {
                    return true; // Solution found
                }
                nodeColors[currentNode] = -1; // Backtrack
            }
        }

        return false; // No valid coloring for this node
    }

    private static boolean isValidColor(Graph graph, int node, int color, int[] nodeColors) {
        for (int neighbor : graph.getNeighbors(node)) {
            if (nodeColors[neighbor] == color) {
                return false; // Conflict with neighbor
            }
        }
        return true;
    }
}

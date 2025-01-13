
import mpi.MPI;
import mpi.Request;

import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;

public class DistributedGraphColoring {
    public static int[] graphColoringMain(int mpiSize, Graph graph, int colorsNumber) throws Exception {
        int[] colorAssignments = graphColoringRecursive(0, graph, colorsNumber, new int[graph.getNodesNumber()], 0, mpiSize, 0);

        if (colorAssignments[0] == -1) {
            throw new Exception("No solution found!");
        }

        return colorAssignments;
    }

    private static int[] graphColoringRecursive(
            int nodeId, Graph graph, int colorsNumber, int[] colorAssignments, int mpiRank, int mpiSize, int depth) {
        int nodesNumber = graph.getNodesNumber();

        if (!isColorValid(nodeId, colorAssignments, graph)) {
            return fillArray(nodesNumber, -1);
        }

        if (nodeId + 1 == graph.getNodesNumber()) {
            return colorAssignments;
        }

        int coefficient = (int) Math.pow(colorsNumber, depth);
        int colorIndex = 0;
        int destination = mpiRank + coefficient * (colorIndex + 1);

        while (colorIndex + 1 < colorsNumber && destination < mpiSize) {
            colorIndex++;
            destination = mpiRank + coefficient * (colorIndex + 1);
        }

        int nextNode = nodeId + 1;
        int nextColorCombinationLevel = depth + 1;

        for (int currentColorIndex = 1; currentColorIndex < colorIndex; currentColorIndex++) {
            destination = mpiRank + coefficient * currentColorIndex;

            int[] data = new int[]{mpiRank, nextNode, nextColorCombinationLevel};
            MPI.COMM_WORLD.Send(data, 0, data.length, MPI.INT, destination, 0);

            int[] nextColorAssignments = Arrays.copyOf(colorAssignments, colorAssignments.length);
            nextColorAssignments[nextNode] = currentColorIndex;

            MPI.COMM_WORLD.Send(nextColorAssignments, 0, nodesNumber, MPI.INT, destination, 0);
        }

        int[] nextColorAssignments = Arrays.copyOf(colorAssignments, colorAssignments.length);
        nextColorAssignments[nextNode] = 0;

        int[] result = graphColoringRecursive(nextNode, graph, colorsNumber, nextColorAssignments, mpiRank, mpiSize, nextColorCombinationLevel);
        if (result[0] != -1) {
            return result;
        }

        for (int currentColorIndex = 1; currentColorIndex < colorIndex; currentColorIndex++) {
            destination = mpiRank + coefficient * currentColorIndex;
            result = new int[nodesNumber];

            MPI.COMM_WORLD.Recv(result, 0, nodesNumber, MPI.INT, destination, MPI.ANY_TAG);
            if (result[0] != -1) {
                return result;
            }
        }

        for (int currentColorIndex = colorIndex; currentColorIndex < colorsNumber; currentColorIndex++) {
            nextColorAssignments = Arrays.copyOf(colorAssignments, colorAssignments.length);
            nextColorAssignments[nextNode] = currentColorIndex;

            result = graphColoringRecursive(nextNode, graph, colorsNumber, nextColorAssignments, mpiRank, mpiSize, nextColorCombinationLevel);

            if (result[0] != -1) {
                return result;
            }
        }

        return result;
    }

    public static void graphColoringChild(int mpiRank, int mpiSize, Graph graph, int colorsNumber) {
        int nodesNumber = graph.getNodesNumber();

        int[] data = new int[3];
        MPI.COMM_WORLD.Recv(data, 0, data.length, MPI.INT, MPI.ANY_SOURCE, MPI.ANY_TAG);

        int parent = data[0];
        int nodeId = data[1];
        int colorCombinationLevel = data[2];

        int[] colorAssignments = new int[nodesNumber];
        MPI.COMM_WORLD.Recv(colorAssignments, 0, nodesNumber, MPI.INT, MPI.ANY_SOURCE, MPI.ANY_TAG);

        int[] result = graphColoringRecursive(nodeId, graph, colorsNumber, colorAssignments, mpiRank, mpiSize, colorCombinationLevel);

        MPI.COMM_WORLD.Send(result, 0, nodesNumber, MPI.INT, parent, 0);
    }

    private static int[] fillArray(int length, int value) {
        int[] array = new int[length];
        Arrays.fill(array, value);
        return array;
    }

    private static boolean isColorValid(int node, int[] colorAssignments, Graph graph) {
        for (int current = 0; current < node; current++) {
            if (graph.hasEdge(node, current) && colorAssignments[node] == colorAssignments[current]) {
                return false;
            }
        }
        return true;
    }
}

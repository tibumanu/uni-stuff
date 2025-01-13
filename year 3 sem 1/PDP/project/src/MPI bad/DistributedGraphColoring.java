package MPI;
import mpi.MPI;
import mpi.Request;

import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;

public class DistributedGraphColoring {

    // Master process (rank 0) function
    static void colorGraphMaster(Graph graph, int nColors, int size) {
        int nodes = graph.getNodesNumber();
        int nodesPerWorker = nodes / (size - 1); // divide nodes among workers

        // Send portions of the graph to each worker
        for (int i = 1; i < size; i++) {
            int startNode = (i - 1) * nodesPerWorker;
            int endNode = (i == size - 1) ? nodes - 1 : i * nodesPerWorker - 1;
            System.out.println("Master sending node range [" + startNode + ", " + endNode + "] to worker " + i);
            MPI.COMM_WORLD.Send(new int[]{startNode, endNode}, 0, 2, MPI.INT, i, 0);
        }

        // Receive boundary info from workers
//        for (int i = 1; i < size; i++) {
//            int[] boundaryInfo = new int[1]; // Expecting just one value for boundary info
//            System.out.println("Master waiting to receive boundary info from worker " + i);
//            MPI.COMM_WORLD.Recv(boundaryInfo, 0, 1, MPI.INT, i, 2); // Boundary info from workers
//            System.out.println("Master received boundary info from worker " + i + ": " + boundaryInfo[0]);
//        }

        // Receive the coloring results from workers
        List<int[]> receivedColorings = new ArrayList<>();
        for (int i = 1; i < size; i++) {
            int[] result = new int[nodes];
            System.out.println("Master waiting to receive results from worker " + i);
            MPI.COMM_WORLD.Recv(result, 0, nodes, MPI.INT, i, 1); // Expecting coloring results
            receivedColorings.add(result);
            System.out.println("Master received result from worker " + i);
        }

        // Combine the results and check if the solution is valid
        int[] finalColors = new int[graph.getNodesNumber()];
        Arrays.fill(finalColors, -1);
        for (int[] partialColors : receivedColorings) {
            for (int i = 0; i < finalColors.length; i++) {
                if (partialColors[i] != -1) {
                    finalColors[i] = partialColors[i];
                }
            }
        }

        boolean solutionFound = isValidSolution(graph, finalColors);

        System.out.println("Graph's coloring:");
        for (int i = 0; i < nodes; i++) {
            System.out.println(i + " -> color: " + finalColors[i]);
        }

        if (solutionFound) {
            System.out.println("Solution found!");
        } else {
            System.out.println("No solution found!");
        }
    }

    // Worker function
    static void colorGraphWorker(int rank, Graph graph, int nColors) {
        // Receive the portion of the graph assigned by the master
        int[] nodeRange = new int[2];
        System.out.println("Worker " + rank + " waiting to receive node range.");
        MPI.COMM_WORLD.Recv(nodeRange, 0, 2, MPI.INT, 0, 0);
        System.out.println("Worker " + rank + " received node range: [" + nodeRange[0] + ", " + nodeRange[1] + "]");

        int startNode = nodeRange[0];
        int endNode = nodeRange[1];

        // Perform graph coloring on the assigned nodes
        int[] nodeColors = new int[graph.getNodesNumber()];
        Arrays.fill(nodeColors, -1);

        solveGraphColoring(rank, nodeColors, startNode, endNode, nColors);

//        // After solving the coloring, send boundary info to neighboring workers
//        System.out.println("Worker " + rank + " sending boundary info to neighbors.");
//        sendBoundaryInfoToNeighbors(rank, nodeColors);
//
//        // Send coloring results to master
//        System.out.println("Worker " + rank + " sending final coloring to master.");
//        MPI.COMM_WORLD.Send(nodeColors, 0, graph.getNodesNumber(), MPI.INT, 0, 1); // Send coloring results
//
    }



    // Send boundary info to the master directly (not to other workers)
    private static void sendBoundaryInfoToMaster(int rank, int[] nodeColors, int startNode, int endNode) {
        // Send boundary info (first and last node of the range)
        if (rank != 0) {
            System.out.println("Worker " + rank + " sending boundary info to master.");
            MPI.COMM_WORLD.Send(new int[]{nodeColors[startNode], nodeColors[endNode]}, 0, 2, MPI.INT, 0, 2); // Sending boundary nodes' colors to master
        }
    }


    // Send boundary info to neighboring workers first
//    private static void sendBoundaryInfoToNeighbors(int rank, int[] nodeColors) {
//        // Send boundary info to the next worker (send only the last node color)
//        if (rank < MPI.COMM_WORLD.Size() - 1) {
//            System.out.println("Worker " + rank + " sending boundary info to rank " + (rank + 1));
//            MPI.COMM_WORLD.Send(new int[]{nodeColors[nodeColors.length - 1]}, 0, 1, MPI.INT, rank + 1, 2);  // Send last node's color
//        }
//
//        // Send boundary info to the previous worker (send only the first node color)
//        if (rank > 0) {
//            System.out.println("Worker " + rank + " sending boundary info to rank " + (rank - 1));
//            MPI.COMM_WORLD.Send(new int[]{nodeColors[0]}, 0, 1, MPI.INT, rank - 1, 2);  // Send the first node's color
//        }
//    }

    private static void sendBoundaryInfoToNeighbor(int rank, int[] nodeColors, int startNode, int endNode) {
        // If not the first worker, send the color of the first node to the previous worker
        if (rank > 0) {
            int firstNodeColor = nodeColors[startNode]; // color of first node in range
            MPI.COMM_WORLD.Send(new int[] {firstNodeColor}, 0, 1, MPI.INT, rank - 1, 2);
        }

        // If not the last worker, send the color of the last node to the next worker
        if (rank < MPI.COMM_WORLD.Size() - 1) {
            int lastNodeColor = nodeColors[endNode]; // color of last node in range
            MPI.COMM_WORLD.Send(new int[] {lastNodeColor}, 0, 1, MPI.INT, rank + 1, 3);
        }
    }

    // Receive boundary info from adjacent workers (for worker's boundaries to be updated)
    private static void receiveBoundaryInfoFromNeighbor(int rank, int[] nodeColors, int startNode, int endNode) {
        // If not the first worker, receive the color of the first node from the previous worker
        if (rank > 0) {
            int[] prevWorkerColor = new int[1];
            MPI.COMM_WORLD.Recv(prevWorkerColor, 0, 1, MPI.INT, rank - 1, 3);
            nodeColors[startNode - 1] = prevWorkerColor[0]; // Save the boundary color from previous worker
        }

        // If not the last worker, receive the color of the last node from the next worker
        if (rank < MPI.COMM_WORLD.Size() - 1) {
            int[] nextWorkerColor = new int[1];
            MPI.COMM_WORLD.Recv(nextWorkerColor, 0, 1, MPI.INT, rank + 1, 2);
            nodeColors[endNode + 1] = nextWorkerColor[0]; // Save the boundary color from next worker
        }
    }
//    private static void receiveBoundaryInfoFromNeighbor(int rank, int[] nodeColors, int startNode, int endNode) {
//        // Receive boundary info from the previous worker (if applicable)
//        if (rank > 0) {
//            // Worker receives the color for the first boundary node of the previous range
//            MPI.COMM_WORLD.Recv(new int[]{nodeColors[startNode]}, 0, 1, MPI.INT, rank - 1, 2);
//            System.out.println("Worker " + rank + " received boundary info from rank " + (rank - 1));
//        }
//
//        // Receive boundary info from the next worker (if applicable)
//        if (rank < MPI.COMM_WORLD.Size() - 1) {
//            // Worker receives the color for the last boundary node of the next range
//            MPI.COMM_WORLD.Recv(new int[]{nodeColors[endNode]}, 0, 1, MPI.INT, rank + 1, 2);
//            System.out.println("Worker " + rank + " received boundary info from rank " + (rank + 1));
//        }
//    }

    private static void sendBoundaryInfo(int rank, int[] nodeColors) {
        // Send boundary info directly to the master (rank 0)
        if (rank != 0) {
            System.out.println("Worker " + rank + " sending boundary info to master.");
            // Send boundary info to master
            MPI.COMM_WORLD.Send(new int[]{nodeColors[0]}, 0, 1, MPI.INT, 0, 2); // Sending first node's color to master
        }
    }

    // Receive boundary information with logging
    private static void receiveBoundaryInfo(int rank, int[] nodeColors) {
        if (rank > 0) {
            System.out.println("Worker " + rank + " waiting to receive boundary info from rank " + (rank - 1));
            MPI.COMM_WORLD.Recv(new int[]{nodeColors[0]}, 0, 1, MPI.INT, rank - 1, 2);
            System.out.println("Worker " + rank + " received boundary info from rank " + (rank - 1));
        }

        if (rank < MPI.COMM_WORLD.Size() - 1) {
            System.out.println("Worker " + rank + " waiting to receive boundary info from rank " + (rank + 1));
            MPI.COMM_WORLD.Recv(new int[]{nodeColors[nodeColors.length - 1]}, 0, 1, MPI.INT, rank + 1, 2);
            System.out.println("Worker " + rank + " received boundary info from rank " + (rank + 1));
        }
    }


    // Simple backtracking function to solve the graph coloring (for assigned range)
    public static void solveGraphColoring(int rank, int[] nodeColors, int startNode, int endNode, int colors) {
//        MPI.COMM_WORLD.Barrier();
//
//        // Receive boundary info from neighbors
//        System.out.println("Worker " + rank + " sending boundary info to neighbors.");
//        sendBoundaryInfoToNeighbor(rank, nodeColors, startNode, endNode);
//
//        //! program hangs here
//
//        System.out.println("Worker " + rank + " receiving boundary info from neighbors.");
//        receiveBoundaryInfoFromNeighbor(rank, nodeColors, startNode, endNode);

        final int BOUNDARY_TAG = 100; // Tag for boundary info messages

        // Non-blocking send
        System.out.println("Worker " + rank + " sending boundary info to neighbors.");
        mpi.Request sendRequest = MPI.COMM_WORLD.Isend(nodeColors, startNode, endNode - startNode + 1, MPI.INT, rank, BOUNDARY_TAG);

        // Non-blocking receive
        System.out.println("Worker " + rank + " receiving boundary info from neighbors.");
        mpi.Request recvRequest = MPI.COMM_WORLD.Irecv(nodeColors, startNode, endNode - startNode + 1, MPI.INT, rank, BOUNDARY_TAG);

        // Wait for the send and receive to complete
        sendRequest.Wait();
        recvRequest.Wait();

        // Color the nodes in the range
        for (int node = startNode; node <= endNode; node++) {
            boolean validColorFound = false;
            for (int color = 0; color < colors; color++) {
                if (isColorValid(node, color, nodeColors, startNode, endNode)) {
                    nodeColors[node] = color; // Assign valid color
                    validColorFound = true;
                    System.out.println("Worker " + rank + " assigned color " + color + " to node " + node);
                    break; // Proceed to next node if color is found
                }
            }
            if (!validColorFound) {
                System.out.println("No valid color found for node " + node);
                return; // If no color is found, exit the coloring function
            }
        }

        //System.out.println("Worker " + rank + " finished coloring assigned nodes. Sending boundary info to neighbors.");
        //sendBoundaryInfoToNeighbor(rank, nodeColors, startNode, endNode);

        // Send final coloring to the master
        System.out.println("Worker " + rank + " sending final coloring to master: " + Arrays.toString(nodeColors));
        MPI.COMM_WORLD.Send(nodeColors, 0, nodeColors.length, MPI.INT, 0, 1); // Send coloring results

    }

    // Check if the current color assignment is valid
    private static boolean isColorValid(int node, int color, int[] nodeColors, int startNode, int endNode) {
        // print all parameters
        System.out.println("node: " + node + " color: " + color + " nodeColors: " + Arrays.toString(nodeColors) + " startNode: " + startNode + " endNode: " + endNode);

        // Check local neighbors within the worker's range
        // Check left neighbor (node - 1)
        if (node > startNode && nodeColors[node - 1] == color) {
            return false; // Conflict with the previous node within the worker's range
        }

        // Check right neighbor (node + 1)
        if (node < endNode && nodeColors[node + 1] == color) {
            return false; // Conflict with the next node within the worker's range
        }

        // Check boundary conditions with adjacent workers' boundary nodes
        if (node == startNode) { // Left boundary
            if (nodeColors[node] == color) {
                return false; // Conflict with previous worker's boundary node
            }
        }

        if (node == endNode) { // Right boundary
            if (nodeColors[node] == color) {
                return false; // Conflict with next worker's boundary node
            }
        }


        return true;
    }

    // Check if the coloring solution is valid across worker boundaries
    private static boolean isValidSolution(Graph graph, int[] finalColors) {
        int nodes = graph.getNodesNumber();
        for (int i = 0; i < nodes; i++) {
            int color = finalColors[i];
            for (int neighbor : graph.getNeighbors(i)) {
                if (finalColors[neighbor] == color) {
                    return false; // Conflict found
                }
            }
        }
        return true; // No conflicts found, valid solution
    }
}

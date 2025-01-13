import mpi.MPI;

import java.util.Arrays;

public class Main {
    public static void main(String[] args) throws Exception {
        MPI.Init(args);
        int rank = MPI.COMM_WORLD.Rank();
        int size = MPI.COMM_WORLD.Size();

        Graph graph1 = new Graph(15);

        graph1.addEdge(0, 1);
        graph1.addEdge(1, 2);
        graph1.addEdge(1, 3);
        graph1.addEdge(2, 3);
        graph1.addEdge(3, 4);
        graph1.addEdge(4, 5);
        graph1.addEdge(5, 6);
        graph1.addEdge(6, 7);
        graph1.addEdge(7, 8);
        graph1.addEdge(8, 9);
        graph1.addEdge(9, 10);
        graph1.addEdge(10, 11);
        graph1.addEdge(11, 12);
        graph1.addEdge(12, 13);
        graph1.addEdge(13, 14);

        graph1.addEdge(0, 2);
        graph1.addEdge(3, 5);
        graph1.addEdge(6, 8);
        graph1.addEdge(9, 11);
        graph1.addEdge(12, 14);
        graph1.addEdge(0, 14);
        graph1.addEdge(1, 13);
        graph1.addEdge(4, 10);
        graph1.addEdge(7, 9);
        graph1.addEdge(2, 8);
        int nColors = 4;

        Graph graph2 = new Graph(6);
        graph2.addEdge(0, 1);
        graph2.addEdge(0, 3);
        graph2.addEdge(1, 2);
        graph2.addEdge(1, 4);
        graph2.addEdge(2, 5);
        graph2.addEdge(3, 4);
        graph2.addEdge(4, 5);
        graph2.addEdge(1, 3);

        nColors = 2;

        if (rank == 0) {
            System.out.println(graph2);
            System.out.println("Main process");
            long start = System.nanoTime();
            int[] solution = DistributedGraphColoring.graphColoringMain(size, graph2, nColors);
            long stop = System.nanoTime();

            long time = stop - start;

            System.out.println("Final solution: ");
            for (int i = 0; i < graph2.getNodesNumber(); i++){
                System.out.println(i + ": " + solution[i]);
            }
            System.out.println("Time: " + time / 1000000 + " ms");
        } else {
           // System.out.println("Process number: "+ rank);

            DistributedGraphColoring.graphColoringChild(rank, size, graph2, nColors);
        }

        MPI.Finalize();
        /*Graph graph1 = new Graph(4);
        graph1.addEdge(0,1);
        graph1.addEdge(1,2);
        graph1.addEdge(1,3);
        graph1.addEdge(2,3);


        int colors = 3; // Number of colors available
        int threads = 6; // Number of threads to use

        try {
            int[] result = ThreadedGraphColoring.colorGraph(graph1, colors, threads);
            System.out.println("Coloring of the graph: ");
            for (int i = 0; i < result.length; i++) {
                System.out.println("Node " + i + " -> Color " + result[i]);
            }
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }



        *//*
        0 -- 1 -- 2
        |    |    |
        3 -- 4 -- 5 should use 3 colors
         */
        /*
        Graph graph2 = new Graph(6);
        graph2.addEdge(0, 1);
        graph2.addEdge(0, 3);
        graph2.addEdge(1, 2);
        graph2.addEdge(1, 4);
        graph2.addEdge(2, 5);
        graph2.addEdge(3, 4);
        graph2.addEdge(4, 5);

        colors = 3;
        threads = 6;

        try{
            int[] result = ThreadedGraphColoring.colorGraph(graph2, colors, threads);
            System.out.println("Coloring of the graph: ");
            for (int i = 0; i < result.length; i++) {
                System.out.println("Node " + i + " -> Color " + result[i]);
            }
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }

        Graph graph3 = Graph.generateRandomGraphWithEdgeForEachNode(15, 25);
        System.out.println(graph3);

        colors = 7;
        threads = 15;

        try{
            int[] result = ThreadedGraphColoring.colorGraph(graph3, colors, threads);
            System.out.println("Coloring of the graph: ");
            for (int i = 0; i < result.length; i++) {
                System.out.println("Node " + i + " -> Color " + result[i]);
            }
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
*/


//
//        int threadsNumber = 10;
//
//        //Example 1
//        Graph graph1 = new Graph(4);
//        graph1.addEdge(0,1);
//        graph1.addEdge(1,2);
//        graph1.addEdge(1,3);
//        graph1.addEdge(2,3);
//
//        Colors colors1 = new Colors(2);
//        colors1.addColor(0,"blue");
//        colors1.addColor(1,"yellow");
//        colors1.addColor(2,"red");
//
//        try {
//            long startTime = System.nanoTime();
//            System.out.println(GraphColoring.getColoredGraph(threadsNumber, graph1, colors1));
//            long endTime = System.nanoTime();
//            System.out.println("Execution time: " + (endTime - startTime) / 1000000 + " ms");
//        }catch (Exception e){
//            System.out.println("Related to graph 1:");
//            System.out.println(e);
//        }
//
//        //Example 2
//
//        Graph graph2 = new Graph(5);
//        graph2.addEdge(0,1);
//        graph2.addEdge(1,2);
//        graph2.addEdge(2,3);
//        graph2.addEdge(3,4);
//        graph2.addEdge(4,0);
//        graph2.addEdge(2,0);
//        graph2.addEdge(0,4);
//        graph2.addEdge(4,3);
//        graph2.addEdge(3,1);
//
//        Colors colors2 = new Colors(3);
//        colors2.addColor(0, "red");
//        colors2.addColor(1, "green");
//        colors2.addColor(2, "blue");
//
//        try {
//            long startTime = System.nanoTime();
//            System.out.println(GraphColoring.getColoredGraph(threadsNumber, graph2, colors2));
//            long endTime = System.nanoTime();
//            System.out.println("Execution time: " + (endTime - startTime) / 1000000 + " ms");
//        }catch (Exception e){
//            System.out.println(e);
//        }
//
//        //Example 3
//        Graph graph3 = Graph.generateRandomGraph(10);
//        Colors colors3 = new Colors(5);
//        colors3.addColor(0, "red");
//        colors3.addColor(1, "green");
//        colors3.addColor(2, "blue");
//        colors3.addColor(3, "yellow");
//        colors3.addColor(4, "pink");
//        try {
//            long startTime = System.nanoTime();
//            System.out.println(GraphColoring.getColoredGraph(threadsNumber, graph3, colors3));
//            long endTime = System.nanoTime();
//            System.out.println("Execution time: " + (endTime - startTime) / 1000000 + " ms");
//        } catch (Exception exception) {
//            System.out.println("An error occurred");
//            exception.printStackTrace();
//        }
    }
}

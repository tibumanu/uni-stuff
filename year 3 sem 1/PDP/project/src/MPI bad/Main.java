package MPI;

import MPI.Graph;
import MPI.DistributedGraphColoring.*;
import mpi.MPI;

import static MPI.DistributedGraphColoring.colorGraphMaster;
import static MPI.DistributedGraphColoring.colorGraphWorker;

public class Main {
    public static void main(String[] args) {
        MPI.Init(args);

        int rank = MPI.COMM_WORLD.Rank();
        int size = MPI.COMM_WORLD.Size();

        Graph graph1 = new Graph(4);
        graph1.addEdge(0,1);
        graph1.addEdge(1,2);
        graph1.addEdge(1,3);
        graph1.addEdge(2,3);
        int colors = 3; // Number of colors available

        if(rank == 0){
            colorGraphMaster(graph1, colors, size);
        }
        else {
            colorGraphWorker(rank, graph1, colors);
        }

        MPI.Finalize();

        /*
        0 -- 1 -- 2
        |    |    |
        3 -- 4 -- 5 should use >=2 colors
         */
        Graph graph2 = new Graph(6);
        graph2.addEdge(0, 1);
        graph2.addEdge(0, 3);
        graph2.addEdge(1, 2);
        graph2.addEdge(1, 4);
        graph2.addEdge(2, 5);
        graph2.addEdge(3, 4);
        graph2.addEdge(4, 5);


//        Graph graph2 = Graph.generateRandomGraph(10);
//        Colors colors2 = new Colors(5);
//        colors2.addColor(0, "red");
//        colors2.addColor(1, "green");
//        colors2.addColor(2, "blue");
//        colors2.addColor(3, "yellow");
//        colors2.addColor(4, "pink");
//
//        if (rank==0){
//            System.out.println("Main process");
//
//            try{
//                long start = System.nanoTime();
//
//                System.out.println(GraphColoring.graphColoringMain(size,graph2,colors2));
//                long stop = System.nanoTime();
//
//                long time = stop - start;
//                System.out.println("Time: " + time / 1000000 + " ms");
//            } catch (Exception e) {
//                e.printStackTrace();
//            }
//        }
//        else {
//            System.out.println("Process number: "+ rank);
//
//            int colorsNumber = colors2.getColorsNumber();
//
//            GraphColoring.graphColoringChild(rank, size, graph2, colorsNumber);
//        }
//        MPI.Finalize();

    }
}


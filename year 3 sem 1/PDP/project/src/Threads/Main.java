package Threads;

public class Main {
    public static void main(String[] args) {
        Graph graph1 = new Graph(4);
        graph1.addEdge(0,1);
        graph1.addEdge(1,2);
        graph1.addEdge(1,3);
        graph1.addEdge(2,3);


        int colors = 3;
        int threads = 6;

        try {
            int[] result = ThreadedGraphColoring.colorGraph(graph1, colors, threads);
            System.out.println("Coloring of the graph: ");
            for (int i = 0; i < result.length; i++) {
                System.out.println("Node " + i + " -> Color " + result[i]);
            }
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }



        /*
        0 -- 1 -- 2
        |    |    |
        3 -- 4 -- 5 should use >=2 colors
         */
//        Graph graph2 = new Graph(6);
//        graph2.addEdge(0, 1);
//        graph2.addEdge(0, 3);
//        graph2.addEdge(1, 2);
//        graph2.addEdge(1, 4);
//        graph2.addEdge(2, 5);
//        graph2.addEdge(3, 4);
//        graph2.addEdge(4, 5);
        Graph graph2 = Graph.generateRandomGraphWithEdgeForEachNode(10, 20);

        colors = 2;
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

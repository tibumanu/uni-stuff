import model.Graph;
import solver.HamiltonianCycleFinder;
import java.util.List;


public class Main {
    public static void main(String[] args) throws InterruptedException {

        Graph graph = new Graph();

        for (int i = 0; i < 6; i++) {
            graph.addNode(i);
        }

        //graph.addEdge(0, 1);
        graph.addEdge(0, 4);
        graph.addEdge(1, 2);
        graph.addEdge(2, 3);

        graph.addEdge(3, 4);
        graph.addEdge(4, 5);
        graph.addEdge(5, 0);

        graph.addEdge(1, 5);
        graph.addEdge(4, 2);
        graph.addEdge(3, 1);

        System.out.println(graph);

        HamiltonianCycleFinder finder = new HamiltonianCycleFinder(graph);
        List<Integer> cycle = finder.findHamiltonianCycle();

        if (cycle != null) {
            System.out.println("Hamiltonian cycle found: " + cycle);
        } else {
            System.out.println("No hamiltonian cycle found.");
        }
    }
}
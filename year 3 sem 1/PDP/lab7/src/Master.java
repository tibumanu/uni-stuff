import mpi.MPI;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Master {
    public Polynomial executeMaster(Polynomial p_1, Polynomial p_2, String algorithm, int processes) {
        System.out.println("=== master process: distributing tasks...");

        // Distribute tasks to worker processes
        distributeTasks(p_1, p_2, processes);

        // Gather results from worker processes
        return gatherResults(processes, p_1.getDegree() + p_2.getDegree());
    }

    private void distributeTasks(Polynomial p_1, Polynomial p_2, int processes) {
        int chunkSize = (p_1.getDegree() + 1) / (processes - 1); // Divide workload
        int start, end;

        for (int i = 1; i < processes; i++) {
            start = (i - 1) * chunkSize;
            end = (i == processes - 1) ? p_1.getDegree() + 1 : i * chunkSize;

            // Create a sublist for the worker's chunk
            List<Integer> sublistP1 = p_1.getCoefficients().subList(start, end);

            // Send the sublist of p_1, the entire p_2, and the start index to the worker
            MPI.COMM_WORLD.Send(new Object[]{new Polynomial(sublistP1)}, 0, 1, MPI.OBJECT, i, 0);
            MPI.COMM_WORLD.Send(new Object[]{p_2}, 0, 1, MPI.OBJECT, i, 0);
            MPI.COMM_WORLD.Send(new int[]{start}, 0, 1, MPI.INT, i, 0);
        }
    }

    private Polynomial gatherResults(int processes, int resultSize) {
        List<Integer> finalResult = new ArrayList<>(Collections.nCopies(resultSize + 1, 0));

        for (int i = 1; i < processes; i++) {
            Object[] partialResult = new Object[1];
            MPI.COMM_WORLD.Recv(partialResult, 0, 1, MPI.OBJECT, i, 0);
            List<Integer> partialCoefficients = ((Polynomial) partialResult[0]).getCoefficients();

            // Combine partial results
            for (int j = 0; j < partialCoefficients.size(); j++) {
                finalResult.set(j, finalResult.get(j) + partialCoefficients.get(j));
            }
        }

        return new Polynomial(finalResult);
    }
}

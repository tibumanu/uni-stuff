import mpi.MPI;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Worker {
    public void executeWorker(String algorithm, int rank) {
        Object[] p_1 = new Object[1];
        Object[] p_2 = new Object[1];
        int[] startIndex = new int[1];

        System.out.println("= worker " + rank + " started");

        MPI.COMM_WORLD.Recv(p_1, 0, 1, MPI.OBJECT, 0, 0);
        MPI.COMM_WORLD.Recv(p_2, 0, 1, MPI.OBJECT, 0, 0);
        MPI.COMM_WORLD.Recv(startIndex, 0, 1, MPI.INT, 0, 0);

        Polynomial poly_1 = (Polynomial) p_1[0];
        Polynomial poly_2 = (Polynomial) p_2[0];

        Polynomial result;
        if ("karatsuba".equalsIgnoreCase(algorithm)) {
            result = karatsubaMultiply(poly_1, poly_2, startIndex[0]);
        } else {
            result = regularMultiply(poly_1, poly_2, startIndex[0]);
        }

        MPI.COMM_WORLD.Send(new Object[]{result}, 0, 1, MPI.OBJECT, 0, 0);
    }

    private Polynomial regularMultiply(Polynomial partial_p_1, Polynomial full_p_2, int startIndex) {
        int degree = startIndex + partial_p_1.getDegree() + full_p_2.getDegree();
        List<Integer> result = new ArrayList<>(Collections.nCopies(degree + 1, 0));

        for (int i = 0; i <= partial_p_1.getDegree(); i++) {
            for (int j = 0; j <= full_p_2.getDegree(); j++) {
                result.set(startIndex + i + j, result.get(startIndex + i + j) +
                        partial_p_1.getCoefficients().get(i) * full_p_2.getCoefficients().get(j));
            }
        }

        return new Polynomial(result);
    }

    private Polynomial karatsubaMultiply(Polynomial partial_p_1, Polynomial full_p_2, int startIndex) {
        Polynomial partialResult = SequentialKaratsubaMultiplication.multiply(partial_p_1, full_p_2);

        return partialResult.shift(startIndex);
    }
}

import mpi.MPI;
import mpi.MPIException;
import java.util.ArrayList;
import java.util.List;

/*
> mpjrun.bat -np 6 -cp out/production/lab7 Main
    poly1.degree    = 50_000
    poly2.degree    = 33_333
    regular avg     = 5000ms
    karatsuba avg   = 3000ms

from lab5, with the same polynomial degrees:
    seq regular avg     = 13000ms
    prl regular avg     = 89000ms
    seq karatsuba avg   = 3500ms
    prl karatsuba avg   = 2100ms
*/
public class Main {
    public static void main(String[] args) throws InterruptedException {
        Polynomial p_1 = new Polynomial(100);
        Polynomial p_2 = new Polynomial(100);

        MPI.Init(args);
        int rank = MPI.COMM_WORLD.Rank();
        int size = MPI.COMM_WORLD.Size();

        String algorithm = "regular"; // "regular" or "karatsuba"

        if (rank == 0) { // Master process
            Master master = new Master();

            System.out.println("\n===== starting MPI-based " + algorithm + " multiplication...");
            long start = System.nanoTime();

            Polynomial result = master.executeMaster(p_1, p_2, algorithm, size);

            long end = System.nanoTime();
            System.out.println("===== final result: " + result);
            System.out.println("===== MPI-based " + algorithm + " multiplication time: " + (end - start) / 1e6 + " ms");
        } else { // Worker processes
            Worker worker = new Worker();
            worker.executeWorker(algorithm, rank);
        }

        MPI.Finalize();
    }
}

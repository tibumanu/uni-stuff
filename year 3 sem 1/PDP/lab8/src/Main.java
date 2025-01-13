import mpi.MPI;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        MPI.Init(args);
        final DSM dsm = new DSM();
        dsm.initializeVariables("x", "y", "z");

        if (MPI.COMM_WORLD.Rank() == 0) {
            master(dsm);
        } else {
            worker(dsm);
        }
        System.out.println("Process " + MPI.COMM_WORLD.Rank() + " finished.");
        MPI.Finalize();
    }

    private static void master(final DSM dsm) throws InterruptedException {
        final Thread listenerThread = new Thread(new Listener(dsm));
        listenerThread.start();

        dsm.subscribe("x");
        Thread.sleep(250);
        dsm.compareAndExchange("x", 0, 50);
        Thread.sleep(1000);
        dsm.close();

        listenerThread.join();
    }

    private static void worker(final DSM dsm) throws InterruptedException {
        final Thread listenerThread = new Thread(new Listener(dsm));
        listenerThread.start();

        dsm.subscribe("x");
        Thread.sleep(500);
        dsm.updateVariable("x", 100);

        listenerThread.join();
    }
}

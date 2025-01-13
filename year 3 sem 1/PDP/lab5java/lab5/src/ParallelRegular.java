import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class ParallelRegular {
    public static Polynomial multiply(Polynomial p1, Polynomial p2) throws InterruptedException {
        int degree = p1.getDegree() + p2.getDegree() + 1;
        List<Integer> result = new ArrayList<>(Collections.nCopies(degree, 0));

        int numThreads = Runtime.getRuntime().availableProcessors();
        ExecutorService executor = Executors.newFixedThreadPool(numThreads);

        int stepsPerThread = (degree) / numThreads;
        List<Thread> threads = new ArrayList<>();

        for (int i = 0; i < numThreads; i++) {
            int start = i * stepsPerThread;
            int end = (i == numThreads - 1) ? (p1.getDegree() + 1) : (start + stepsPerThread);

            PolynomialTask task = new PolynomialTask(p1, p2, result, start, end);
            threads.add(new Thread(task));
        }

        for (Thread thread : threads) {
            executor.submit(thread);
        }

        executor.shutdown();
        //executor.awaitTermination(20, TimeUnit.SECONDS);
        while(!executor.isTerminated())
        {
            Thread.sleep(5);
        }

        return new Polynomial(result);
    }
}

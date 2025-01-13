import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class BigNumber {
    public static List<Integer> generateBigNumber(int numDigits) {
        Random random = new Random();
        List<Integer> number = new ArrayList<>();
        for (int i = 0; i < numDigits; i++) {
            number.add(random.nextInt(10));
        }
        if (number.get(numDigits - 1) == 0) {
            number.set(numDigits - 1, random.nextInt(9) + 1);
        }
        return number;
    }

    public static List<Integer> sequentialRegularMultiply(List<Integer> num1, List<Integer> num2) {
        int n = num1.size();
        int m = num2.size();
        List<Integer> result = new ArrayList<>(Collections.nCopies(n + m, 0));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int product = num1.get(i) * num2.get(j);
                result.set(i + j, result.get(i + j) + product);

                if (result.get(i + j) >= 10) {
                    int carry = result.get(i + j) / 10;
                    result.set(i + j, result.get(i + j) % 10);
                    result.set(i + j + 1, result.get(i + j + 1) + carry);
                }
            }
        }
        while (result.size() > 1 && result.get(result.size() - 1) == 0) {
            result.remove(result.size() - 1);
        }
        return result;
    }

    public static List<Integer> karatsubaMultiply(List<Integer> num1, List<Integer> num2) {
        int n = Math.max(num1.size(), num2.size());
        if (n == 1) {
            return sequentialRegularMultiply(num1, num2);
        }

        // Pad with zeros to ensure equal length
        while (num1.size() < n) num1.add(0);
        while (num2.size() < n) num2.add(0);

        int half = n / 2;

        // Split the numbers
        List<Integer> low1 = new ArrayList<>(num1.subList(0, half));
        List<Integer> high1 = new ArrayList<>(num1.subList(half, n));
        List<Integer> low2 = new ArrayList<>(num2.subList(0, half));
        List<Integer> high2 = new ArrayList<>(num2.subList(half, n));

        // Compute the three products
        List<Integer> z0 = karatsubaMultiply(low1, low2);
        List<Integer> z1 = karatsubaMultiply(add(low1, high1), add(low2, high2));
        List<Integer> z2 = karatsubaMultiply(high1, high2);

        // Combine results
        List<Integer> result = new ArrayList<>(Collections.nCopies(n * 2, 0));
        addTo(result, z0, 0); // z0
        addTo(result, subtract(subtract(z1, z0), z2), half); // z1 - z0 - z2
        addTo(result, z2, half * 2); // z2

        // Remove leading zeros
        while (result.size() > 1 && result.get(result.size() - 1) == 0) {
            result.remove(result.size() - 1);
        }
        return result;
    }

    // Parallel regular multiplication
    public static List<Integer> parallelRegularMultiply(List<Integer> num1, List<Integer> num2) throws InterruptedException {
        int n = num1.size();
        int m = num2.size();
        List<Integer> result = new ArrayList<>(Collections.nCopies(n + m, 0));
        int numThreads = Runtime.getRuntime().availableProcessors();
        ExecutorService executor = Executors.newFixedThreadPool(numThreads);

        int stepsPerThread = n / numThreads;

        for (int i = 0; i < numThreads; i++) {
            int start = i * stepsPerThread;
            int end = (i == numThreads - 1) ? n : start + stepsPerThread;

            executor.submit(() -> {
                for (int row = start; row < end; row++) {
                    for (int col = 0; col < m; col++) {
                        int product = num1.get(row) * num2.get(col);
                        synchronized (result) {
                            result.set(row + col, result.get(row + col) + product);

                            // handle carry
                            if (result.get(row + col) >= 10) {
                                int carry = result.get(row + col) / 10;
                                result.set(row + col, result.get(row + col) % 10);
                                result.set(row + col + 1, result.get(row + col + 1) + carry);
                            }
                        }
                    }
                }
            });
        }

        executor.shutdown();
        while (!executor.isTerminated()) {
            Thread.sleep(10);
        }

        return result;
    }

    // helper functions for Karatsuba
    private static List<Integer> add(List<Integer> num1, List<Integer> num2) {
        int size = Math.max(num1.size(), num2.size());
        List<Integer> result = new ArrayList<>(Collections.nCopies(size, 0));

        int carry = 0;
        for (int i = 0; i < size; i++) {
            int digit1 = (i < num1.size()) ? num1.get(i) : 0;
            int digit2 = (i < num2.size()) ? num2.get(i) : 0;

            int sum = digit1 + digit2 + carry;
            result.set(i, sum % 10);
            carry = sum / 10;
        }
        if (carry > 0) {
            result.add(carry);
        }
        return result;
    }

    private static List<Integer> subtract(List<Integer> num1, List<Integer> num2) {
        List<Integer> result = new ArrayList<>(num1);
        for (int i = 0; i < num2.size(); i++) {
            result.set(i, result.get(i) - num2.get(i));
            if (result.get(i) < 0) {
                result.set(i, result.get(i) + 10);
                result.set(i + 1, result.get(i + 1) - 1);
            }
        }
        while (result.size() > 1 && result.get(result.size() - 1) == 0) {
            result.remove(result.size() - 1);
        }
        return result;
    }

    private static void addTo(List<Integer> result, List<Integer> addition, int offset) {
        int carry = 0;
        for (int i = 0; i < addition.size(); i++) {
            int sum = result.get(i + offset) + addition.get(i) + carry;
            result.set(i + offset, sum % 10);
            carry = sum / 10;
        }
        if (carry > 0) {
            result.set(addition.size() + offset, result.get(addition.size() + offset) + carry);
        }
    }

    public static String bigNumberToString(List<Integer> number) {
        StringBuilder sb = new StringBuilder();
        for (int i = number.size() - 1; i >= 0; i--) {
            sb.append(number.get(i));
        }
        return sb.toString();
    }
}

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        polynomialMultiplication();
        // bigNumberMultiplication();
    }

    public static void polynomialMultiplication() throws InterruptedException {
        Polynomial p1 = new Polynomial(50_000);
        Polynomial p2 = new Polynomial(33_333);

//        System.out.println("p_1 = " + p1);
//        System.out.println("p_2 = " + p2);
//        System.out.println("p_1 + p_2 = " + p1.add(p2));
//        System.out.println("p_1 - p_2 = " + p1.subtract(p2));
        // System.out.println("p_2 shifted by 3 = " + p2.shift(3));

        long start = System.nanoTime();
        Polynomial sequentialRegular = SequentialRegular.multiply(p1, p2);
        long end = System.nanoTime();
//        System.out.println("\nsequential regular: " + sequentialRegular);
        System.out.println("time: " + (end - start) / 1e6 + " ms");

        start = System.nanoTime();
        Polynomial parallelRegular = ParallelRegular.multiply(p1, p2);
        end = System.nanoTime();
//        System.out.println("\nparallelized regular: " + parallelRegular);
        System.out.println("time: " + (end - start) / 1e6 + " ms");

        start = System.nanoTime();
        Polynomial sequentialKaratsuba = SequentialKaratsuba.multiply(p1, p2);
        end = System.nanoTime();
//        System.out.println("\nsequential karatsuba: " + sequentialKaratsuba);
        System.out.println("time: " + (end - start) / 1e6 + " ms");

        start = System.nanoTime();
        Polynomial parallelKaratsuba = ParallelKaratsuba.multiply(p1, p2);
        end = System.nanoTime();
//        System.out.println("\nparallelized karatsuba: " + parallelKaratsuba);
        System.out.println("time: " + (end - start) / 1e6 + " ms");
    }

    public static void bigNumberMultiplication() throws InterruptedException {
        List<Integer> num1 = BigNumber.generateBigNumber(166);
        List<Integer> num2 = BigNumber.generateBigNumber(166);

        System.out.println("\nN_1: " + BigNumber.bigNumberToString(num1));
        System.out.println("N_2: " + BigNumber.bigNumberToString(num2));

        long start = System.nanoTime();
        List<Integer> bigNumberSeq = BigNumber.sequentialRegularMultiply(num1, num2);
        long end = System.nanoTime();
        System.out.println("\nsequential regular: " + BigNumber.bigNumberToString(bigNumberSeq));
        System.out.println("time: " + (end - start) / 1e6 + " ms");

        start = System.nanoTime();
        List<Integer> bigNumberReg = BigNumber.parallelRegularMultiply(num1, num2);
        end = System.nanoTime();
        System.out.println("parallelized regular: " + BigNumber.bigNumberToString(bigNumberReg));
        System.out.println("time: " + (end - start) / 1e6 + " ms");

        start = System.nanoTime();
        List<Integer> bigNumberKaratsuba = BigNumber.karatsubaMultiply(new ArrayList<>(num1), new ArrayList<>(num2));
        end = System.nanoTime();
        System.out.println("karatsuba: " + BigNumber.bigNumberToString(bigNumberKaratsuba));
        System.out.println("time: " + (end - start) / 1e6 + " ms");
    }
}

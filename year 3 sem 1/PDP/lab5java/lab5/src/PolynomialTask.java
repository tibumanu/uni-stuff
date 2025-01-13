import java.util.List;

public class PolynomialTask implements Runnable {
    private Polynomial p1, p2;
    private List<Integer> result;
    private int startRow, endRow;

    public PolynomialTask(Polynomial p1, Polynomial p2, List<Integer> result, int startRow, int endRow) {
        this.p1 = p1;
        this.p2 = p2;
        this.result = result;
        this.startRow = startRow;
        this.endRow = endRow;
    }

    @Override
    public void run() {
        for (int i = startRow; i < endRow; i++) {
            for (int j = 0; j <= p2.getDegree(); j++) {
                synchronized (result) {
                    result.set(i + j, result.get(i + j) + p1.getCoefficients().get(i) * p2.getCoefficients().get(j));
                }
            }
        }
    }
}

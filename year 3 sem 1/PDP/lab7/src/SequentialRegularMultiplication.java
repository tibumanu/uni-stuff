import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class SequentialRegularMultiplication {
    public static Polynomial multiply(Polynomial p_1, Polynomial p_2) {
        int degree = p_1.getDegree() + p_2.getDegree();
        List<Integer> result = new ArrayList<>(Collections.nCopies(degree + 1, 0));

        for (int i = 0; i <= p_1.getDegree(); i++) {
            for (int j = 0; j <= p_2.getDegree(); j++) {
                result.set(i + j, result.get(i + j) + p_1.getCoefficients().get(i) * p_2.getCoefficients().get(j));
            }
        }

        return new Polynomial(result);
    }
}

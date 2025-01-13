import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class SequentialRegular {
    public static Polynomial multiply(Polynomial p1, Polynomial p2) {
        int degree = p1.getDegree() + p2.getDegree();
        List<Integer> result = new ArrayList<>(Collections.nCopies(degree + 1, 0));

        for (int i = 0; i <= p1.getDegree(); i++) {
            for (int j = 0; j <= p2.getDegree(); j++) {
                result.set(i + j, result.get(i + j) + p1.getCoefficients().get(i) * p2.getCoefficients().get(j));
            }
        }

        return new Polynomial(result);
    }
}

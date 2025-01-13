import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class Polynomial {
    private List<Integer> coefficients;
    private int degree;

    public Polynomial(List<Integer> coefficients) {
        this.coefficients = new ArrayList<>(coefficients);
        this.degree = calculateDegree();
    }

    public Polynomial(int degree) {
        this.degree = degree;
        this.coefficients = generateRandomPolynomial(this.degree);
    }

    public List<Integer> getCoefficients() {
        return coefficients;
    }

    public int getDegree() {
        return degree;
    }

    // calculate the degree by ignoring trailing zeros
    private int calculateDegree() {
        int deg = coefficients.size() - 1;
        while (deg > 0 && coefficients.get(deg) == 0) {
            deg--;
        }
        return deg;
    }

    public List<Integer> generateRandomPolynomial(int degree) {
        Random random = new Random();
        List<Integer> coefficients = new ArrayList<>();

        for (int i = 0; i <= degree; i++) {
            // between -25 and 25
            coefficients.add(random.nextInt(51) - 25);
            // coefficients.add(i);
        }

        return coefficients;
    }

    public Polynomial add(Polynomial other) {
        int maxDegree = Math.max(this.degree, other.getDegree());
        List<Integer> result = new ArrayList<>(Collections.nCopies(maxDegree + 1, 0));

        for (int i = 0; i <= this.degree; i++) {
            result.set(i, result.get(i) + this.coefficients.get(i));
        }
        for (int i = 0; i <= other.getDegree(); i++) {
            result.set(i, result.get(i) + other.getCoefficients().get(i));
        }

        return new Polynomial(result);
    }

    public Polynomial subtract(Polynomial other) {
        int maxDegree = Math.max(this.degree, other.getDegree());
        List<Integer> result = new ArrayList<>(Collections.nCopies(maxDegree + 1, 0));

        for (int i = 0; i <= this.degree; i++) {
            result.set(i, result.get(i) + this.coefficients.get(i));
        }
        for (int i = 0; i <= other.getDegree(); i++) {
            result.set(i, result.get(i) - other.getCoefficients().get(i));
        }

        return new Polynomial(result);
    }

    // shift polynomial by adding `positions` leading zeros
    public Polynomial shift(int positions) {
        List<Integer> result = new ArrayList<>(Collections.nCopies(positions, 0));
        result.addAll(this.coefficients);
        return new Polynomial(result);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i <= degree; i++) {
            int coeff = coefficients.get(i);
            if (coeff != 0) {
                if (sb.length() > 0 && coeff > 0) {
                    sb.append(" + ");
                } else if (coeff < 0) {
                    sb.append(" - ");
                    coeff = -coeff;
                }
                if (i == 0 || coeff != 1) {
                    sb.append(coeff);
                }
                if (i > 0) {
                    sb.append("x");
                }
                if (i > 1) {
                    sb.append("^").append(i);
                }
            }
        }
        return sb.length() > 0 ? sb.toString() : "0";
    }
}

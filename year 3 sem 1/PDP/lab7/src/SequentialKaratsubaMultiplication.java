public class SequentialKaratsubaMultiplication {
    public static Polynomial multiply(Polynomial p_1, Polynomial p_2) {
        if (p_1.getDegree() < 167 || p_2.getDegree() < 167) {
            return SequentialRegularMultiplication.multiply(p_1, p_2);
        }

        int mid = Math.min(p_1.getDegree(), p_2.getDegree()) / 2;

        Polynomial low_1 = new Polynomial(p_1.getCoefficients().subList(0, mid));
        Polynomial high_1 = new Polynomial(p_1.getCoefficients().subList(mid, p_1.getCoefficients().size()));
        Polynomial low_2 = new Polynomial(p_2.getCoefficients().subList(0, mid));
        Polynomial high_2 = new Polynomial(p_2.getCoefficients().subList(mid, p_2.getCoefficients().size()));

        Polynomial z_0 = multiply(low_1, low_2);
        Polynomial z_1 = multiply(low_1.add(high_1), low_2.add(high_2));
        Polynomial z_2 = multiply(high_1, high_2);

        return z_0.add(z_1.subtract(z_0).subtract(z_2).shift(mid)).add(z_2.shift(2 * mid));
    }
}

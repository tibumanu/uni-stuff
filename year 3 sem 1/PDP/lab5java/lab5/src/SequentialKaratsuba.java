public class SequentialKaratsuba {
    public static Polynomial multiply(Polynomial p1, Polynomial p2) {
        if (p1.getDegree() < 167 || p2.getDegree() < 167) {
            return SequentialRegular.multiply(p1, p2);
        }

        int mid = Math.min(p1.getDegree(), p2.getDegree()) / 2;

        Polynomial low1 = new Polynomial(p1.getCoefficients().subList(0, mid));
        Polynomial high1 = new Polynomial(p1.getCoefficients().subList(mid, p1.getCoefficients().size()));
        Polynomial low2 = new Polynomial(p2.getCoefficients().subList(0, mid));
        Polynomial high2 = new Polynomial(p2.getCoefficients().subList(mid, p2.getCoefficients().size()));

        Polynomial z0 = multiply(low1, low2);
        Polynomial z1 = multiply(low1.add(high1), low2.add(high2));
        Polynomial z2 = multiply(high1, high2);

        return z0.add(z1.subtract(z0).subtract(z2).shift(mid)).add(z2.shift(2 * mid));
    }
}

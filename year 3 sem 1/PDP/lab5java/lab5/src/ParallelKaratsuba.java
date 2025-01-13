public class ParallelKaratsuba {
    public static Polynomial multiply(Polynomial p1, Polynomial p2) throws InterruptedException {
        if (p1.getDegree() < 167 || p2.getDegree() < 167) {
            return SequentialRegular.multiply(p1, p2);
        }

        int mid = Math.min(p1.getDegree(), p2.getDegree()) / 2;

        Polynomial low1 = new Polynomial(p1.getCoefficients().subList(0, mid));
        Polynomial high1 = new Polynomial(p1.getCoefficients().subList(mid, p1.getCoefficients().size()));
        Polynomial low2 = new Polynomial(p2.getCoefficients().subList(0, mid));
        Polynomial high2 = new Polynomial(p2.getCoefficients().subList(mid, p2.getCoefficients().size()));

        Polynomial[] results = new Polynomial[3];
        Thread z0Thread = new Thread(() -> results[0] = SequentialKaratsuba.multiply(low1, low2));
        Thread z1Thread = new Thread(() -> results[1] = SequentialKaratsuba.multiply(low1.add(high1), low2.add(high2)));
        Thread z2Thread = new Thread(() -> results[2] = SequentialKaratsuba.multiply(high1, high2));

        z0Thread.start();
        z1Thread.start();
        z2Thread.start();

        z0Thread.join();
        z1Thread.join();
        z2Thread.join();

        Polynomial z0 = results[0];
        Polynomial z1 = results[1];
        Polynomial z2 = results[2];

        return z0.add(z1.subtract(z0).subtract(z2).shift(mid)).add(z2.shift(2 * mid));
    }
}

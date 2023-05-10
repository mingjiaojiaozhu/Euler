package project_euler;

public class Problem033 {
    public void solution() {
        int numerator = 1;
        int denominator = 1;
        for (int i = 1; i < 10; ++i) {
            for (int j = i + 1; j < 10; ++j) {
                if (0 == (9 * i * j) % (10 * i - j) && (9 * i * j) / (10 * i - j) < 10) {
                    numerator *= i;
                    denominator *= j;
                }
            }
        }
        System.out.println(denominator / commonDivisor(denominator, numerator));
    }

    private int commonDivisor(int i, int j) {
        while (0 != i % j) {
            int auxiliary = i % j;
            i = j;
            j = auxiliary;
        }
        return j;
    }
}

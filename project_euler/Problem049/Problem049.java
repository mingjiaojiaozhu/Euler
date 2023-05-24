package project_euler;

import java.util.Arrays;

public class Problem049 {
    public void solution() {
        int target = 3330;
        int other = 1487;
        int[] terms = new int[2];
        boolean[] digits = new boolean[10];
        for (int i = 10000 - (target << 1) - 1; i > 1000; i -= 2) {
            if (isPrime(i) && i != other) {
                terms[0] = i + target;
                terms[1] = terms[0] + target;
                if (isPrime(terms[0]) && isPrime(terms[1]) && checkDigit(i, terms, digits)) {
                    System.out.printf("%d%d%d\n", i, terms[0], terms[1]);
                    return;
                }
            }
        }
    }

    private boolean isPrime(int value) {
        if (1 != value % 6 && 5 != value % 6) {
            return 2 == value || 3 == value;
        }

        int border = (int) Math.sqrt(value);
        for (int i = 5; i <= border; i += 6) {
            if (0 == value % i || 0 == value % (i + 2)) {
                return false;
            }
        }
        return 1 != value;
    }

    private boolean checkDigit(int value, int[] terms, boolean[] digits) {
        Arrays.fill(digits, false);
        while (0 != value) {
            digits[value % 10] = true;
            value /= 10;
        }

        for (int term : terms) {
            while (0 != term) {
                if (!digits[term % 10]) {
                    return false;
                }
                term /= 10;
            }
        }
        return true;
    }
}

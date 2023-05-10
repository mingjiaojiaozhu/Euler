package project_euler;

import java.util.Arrays;

public class Problem035 {
    public void solution() {
        int target = 1000000;
        int length = (target + 1) >> 1;
        boolean[] primes = new boolean[length];
        Arrays.fill(primes, true);
        primes[0] = false;

        int border = (int) Math.sqrt(target) + 1;
        for (int i = 3; i <= border; i += 2) {
            if (primes[i >> 1]) {
                for (int j = i * i >> 1; j < length; j += i) {
                    primes[j] = false;
                }
            }
        }

        int result = 13;
        for (int i = 101; i < target; i += 2) {
            if (primes[i >> 1] && checkDigits(i) && isCircular(i, primes)) {
                ++result;
            }
        }
        System.out.println(result);
    }

    private boolean checkDigits(int value) {
        while (0 != value) {
            int remainder = value % 10;
            if (1 != remainder && 3 != remainder && 7 != remainder && 9 != remainder) {
                return false;
            }
            value /= 10;
        }
        return true;
    }

    private boolean isCircular(int value, boolean[] primes) {
        int divisor = 1;
        int length = 1;
        while (value / divisor >= 10) {
            divisor *= 10;
            ++length;
        }

        for (int i = 1; i < length; ++i) {
            value = (value % 10) * divisor + value / 10;
            if (!primes[value >> 1]) {
                return false;
            }
        }
        return true;
    }
}

package project_euler;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Problem070 {
    public void solution() {
        int target = 10000000;
        int pivot = (int) Math.sqrt(target);
        int start = getPreviousPrime(pivot);
        int end = getNextPrime(pivot);
        List<Integer> primes = new ArrayList<>();
        primes.add(end);
        int[][] digits = new int[2][10];
        int result = 0;
        while (true) {
            for (int prime : primes) {
                getDigits(start * prime, digits[0]);
                getDigits((start - 1) * (prime - 1), digits[1]);
                if (checkDigits(digits)) {
                    result = start * prime;
                }
            }

            end = getNextPrime(primes.get(primes.size() - 1));
            while (start * end < target) {
                primes.add(end);
                getDigits(start * end, digits[0]);
                getDigits((start - 1) * (end - 1), digits[1]);
                if (checkDigits(digits)) {
                    result = start * end;
                }
                end = getNextPrime(end);
            }

            if (0 != result) {
                System.out.println(result);
                return;
            }
            start = getPreviousPrime(start);
        }
    }

    private int getPreviousPrime(int value) {
        if (0 == (value & 1)) {
            --value;
        } else {
            value -= 2;
        }

        while (!isPrime(value)) {
            value -= 2;
        }
        return value;
    }

    private int getNextPrime(int value) {
        if (0 == (value & 1)) {
            ++value;
        } else {
            value += 2;
        }

        while (!isPrime(value)) {
            value += 2;
        }
        return value;
    }

    private void getDigits(int value, int[] digits) {
        Arrays.fill(digits, 0);
        while (0 != value) {
            ++digits[value % 10];
            value /= 10;
        }
    }

    private boolean checkDigits(int[][] digits) {
        for (int i = 0; i < 10; ++i) {
            if (digits[0][i] != digits[1][i]) {
                return false;
            }
        }
        return true;
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
}

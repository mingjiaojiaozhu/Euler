package project_euler;

import java.util.Arrays;

public class Problem047 {
    public void solution() {
        int target = 4;
        int length = 200000;
        int[] factors = new int[length];
        Arrays.fill(factors, -1);

        int count = 0;
        for (int i = 2; i <= length; ++i) {
            if (target == getFactors(i, factors, length)) {
                ++count;
                if (target == count) {
                    System.out.println(i - 3);
                    return;
                }
            } else {
                count = 0;
            }
        }
    }

    private int getFactors(int value, int[] factors, int length) {
        if (-1 == factors[value - 1]) {
            long index = value;
            while (index <= length) {
                factors[(int) index - 1] = 1;
                index *= value;
            }

            for (int i = Math.min(value - 1, length / value); i >= 2; --i) {
                factors[value * i - 1] = factors[value - 1] + factors[i - 1];
            }
        } else {
            for (int i = Math.min(value - 1, length / value); i >= 2; --i) {
                if (isRelativelyPrime(value, i) && -1 == factors[value * i - 1]) {
                    factors[value * i - 1] = factors[value - 1] + factors[i - 1];
                }
            }
        }
        return factors[value - 1];
    }

    private boolean isRelativelyPrime(int i, int j) {
        while (0 != i % j) {
            int auxiliary = i % j;
            i = j;
            j = auxiliary;
        }
        return 1 == j;
    }
}

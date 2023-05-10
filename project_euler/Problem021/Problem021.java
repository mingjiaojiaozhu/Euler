package project_euler;

import java.util.Arrays;

public class Problem021 {
    public void solution() {
        int target = 10000;
        int[] divisors = new int[target];
        Arrays.fill(divisors, -1);
        for (int i = 2; i <= target; ++i) {
            getDivisorSummation(i, divisors, target);
        }
        for (int i = 1; i < target; ++i) {
            divisors[i] -= i + 1;
        }

        int result = 0;
        for (int i = 2; i <= target; ++i) {
            int divisor = divisors[i - 1];
            if (divisor > i && divisor <= target && divisors[divisor - 1] == i) {
                result += i + divisor;
            }
        }
        System.out.println(result);
    }

    private void getDivisorSummation(int value, int[] divisors, int length) {
        if (-1 == divisors[value - 1]) {
            int index = value;
            int count = 1;
            while (index <= length) {
                divisors[index - 1] = ((int) Math.pow(value, count + 1) - 1) / (value - 1);
                index *= value;
                ++count;
            }

            for (int i = Math.min(value - 1, length / value); i >= 2; --i) {
                divisors[value * i - 1] = divisors[value - 1] * divisors[i - 1];
            }
        } else {
            for (int i = Math.min(value - 1, length / value); i >= 2; --i) {
                if (isRelativelyPrime(value, i) && -1 == divisors[value * i - 1]) {
                    divisors[value * i - 1] = divisors[value - 1] * divisors[i - 1];
                }
            }
        }
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

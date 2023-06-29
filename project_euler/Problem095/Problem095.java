package project_euler;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class Problem095 {
    public void solution() {
        int target = 1000000;
        long[] divisors = new long[target];
        Arrays.fill(divisors, -1L);
        for (int i = 2; i <= target; ++i) {
            getDivisorSummation(i, divisors, target);
        }
        for (int i = 1; i < target; ++i) {
            divisors[i] -= i + 1;
        }

        int result = 0;
        int pivot = 0;
        Set<Integer> chains = new HashSet<>();
        for (int i = 2; i <= target; ++i) {
            int count = getChain(i, divisors, chains, target);
            if (pivot < count) {
                pivot = count;
                result = target;
                for (int value : chains) {
                    if (result > value) {
                        result = value;
                    }
                }
            }
        }
        System.out.println(result);
    }

    private void getDivisorSummation(int value, long[] divisors, int length) {
        if (-1 == divisors[value - 1]) {
            long index = value;
            int count = 1;
            while (index <= length) {
                divisors[(int) index - 1] = ((long) Math.pow(value, count + 1) - 1) / (value - 1);
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

    private int getChain(long value, long[] divisors, Set<Integer> chains, int target) {
        chains.clear();
        chains.add((int) value);

        long pivot = value;
        int count = 0;
        while (true) {
            value = divisors[(int) value - 1];
            if (pivot == value) {
                break;
            }
            if (1 == value || value >= target || chains.contains((int) value)) {
                return 0;
            }

            chains.add((int) value);
            ++count;
        }
        return count;
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

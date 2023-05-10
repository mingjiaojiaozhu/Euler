package project_euler;

import java.util.Arrays;

public class Problem005 {
    public void solution() {
        int target = 20;
        int[] powers = new int[target];
        Arrays.fill(powers, 0);
        for (int i = 2; i <= target; ++i) {
            factorize(i, powers);
        }

        long result = 1L;
        for (int i = 1; i < target; ++i) {
            for (int j = 0; j < powers[i]; ++j) {
                result *= i + 1;
            }
        }
        System.out.println(result);
    }

    private void factorize(int value, int[] powers) {
        int power = 0;
        while (0 == (value & 1)) {
            value >>= 1;
            ++power;
        }
        if (powers[1] < power) {
            powers[1] = power;
        }

        int factor = 3;
        while (factor <= value) {
            power = 0;
            while (0 == value % factor) {
                value /= factor;
                ++power;
            }
            if (powers[factor - 1] < power) {
                powers[factor - 1] = power;
            }
            factor += 2;
        }
    }
}

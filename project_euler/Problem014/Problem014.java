package project_euler;

import java.util.Arrays;

public class Problem014 {
    public void solution() {
        int target = 1000000;
        int[] chains = new int[target];
        Arrays.fill(chains, -1);
        chains[0] = 1;
        chains[1] = 2;

        for (int i = 3; i <= target; ++i) {
            getCollatz(i, chains, target);
        }

        int result = 0;
        int pivot = 0;
        for (int i = 2; i < target; ++i) {
            if (pivot < chains[i]) {
                pivot = chains[i];
                result = i + 1;
            }
        }
        System.out.println(result);
    }

    private int getCollatz(long value, int[] chains, int length) {
        if (value <= length && -1 != chains[(int) value - 1]) {
            return chains[(int) value - 1];
        }

        int result;
        if (0 != (value & 1)) {
            result = getCollatz(3 * value + 1, chains, length) + 1;
        } else {
            result = getCollatz(value >> 1, chains, length) + 1;
        }
        if (value <= length) {
            chains[(int) value - 1] = result;
        }
        return result;
    }
}

package project_euler;

import java.util.Arrays;

public class Problem038 {
    public void solution() {
        boolean[] digits = new boolean[9];
        for (int i = 9487; i >= 9234; --i) {
            Arrays.fill(digits, false);
            if (isPandigital(i, digits) && isPandigital(i << 1, digits)) {
                System.out.printf("%d%d\n", i, i << 1);
                return;
            }
        }
    }

    private boolean isPandigital(int value, boolean[] digits) {
        while (0 != value) {
            int index = value % 10 - 1;
            if (index < 0 || digits[index]) {
                return false;
            }
            digits[index] = true;
            value /= 10;
        }
        return true;
    }
}

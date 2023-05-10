package project_euler;

import java.util.Arrays;

public class Problem052 {
    public void solution() {
        int target = 6;
        int[] pivots = new int[10];
        int[] digits = new int[10];
        int index = 10;
        while (true) {
            getDigits(index, pivots);
            boolean isSame = true;
            for (int i = target; i > 1; --i) {
                getDigits(index * i, digits);
                if (!checkDigits(pivots, digits)) {
                    isSame = false;
                    break;
                }
            }
            if (isSame) {
                System.out.println(index);
                return;
            }
            ++index;
        }
    }

    private void getDigits(int value, int[] digits) {
        Arrays.fill(digits, 0);
        while (0 != value) {
            ++digits[value % 10];
            value /= 10;
        }
    }

    private boolean checkDigits(int[] pivots, int[] digits) {
        for (int i = 0; i < 10; ++i) {
            if (pivots[i] != digits[i]) {
                return false;
            }
        }
        return true;
    }
}

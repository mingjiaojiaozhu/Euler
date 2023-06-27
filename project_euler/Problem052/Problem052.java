package project_euler;

import java.util.Arrays;

public class Problem052 {
    public void solution() {
        int target = 6;
        int[][] digits = new int[2][10];
        int index = 10;
        while (true) {
            getDigits(index, digits[0]);
            boolean isSame = true;
            for (int i = target; i > 1; --i) {
                getDigits(index * i, digits[1]);
                if (!checkDigits(digits)) {
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

    private boolean checkDigits(int[][] digits) {
        for (int i = 0; i < 10; ++i) {
            if (digits[0][i] != digits[1][i]) {
                return false;
            }
        }
        return true;
    }
}

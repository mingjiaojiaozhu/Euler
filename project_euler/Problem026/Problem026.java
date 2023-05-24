package project_euler;

import java.util.ArrayList;
import java.util.List;

public class Problem026 {
    public void solution() {
        int target = 1000;
        List<Integer> remainders = new ArrayList<>();
        int result = 0;
        int pivot = 0;
        for (int i = target - 1; i >= 7; i -= 2) {
            if (isPrime(i)) {
                int count = getDigit(i, remainders);
                if (pivot < count) {
                    pivot = count;
                    result = i;
                }
                if (count == i - 1) {
                    break;
                }
            }
        }
        System.out.println(result);
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

    private int getDigit(int value, List<Integer> remainders) {
        remainders.clear();
        int remainder = 1;
        while (true) {
            remainders.add(remainder);
            remainder = remainder * 10 % value;
            int index = remainders.indexOf(remainder);
            if (-1 != index) {
                return remainders.size() - index;
            }
        }
    }
}

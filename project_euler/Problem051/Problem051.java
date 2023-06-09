package project_euler;

import java.util.ArrayList;
import java.util.List;

public class Problem051 {
    public void solution() {
        int target = 8;
        List<Integer>[] digits = new ArrayList[3];
        for (int i = 0; i < 3; ++i) {
            digits[i] = new ArrayList<>();
        }
        List<Integer> steps = new ArrayList<>();
        int[] auxiliary = new int[3];

        int result = 1111;
        while (true) {
            result = getNextPrime(result);
            if (checkDigits(result, digits) && checkPrimeFamily(result, target, digits, steps, auxiliary)) {
                System.out.println(result);
                return;
            }
        }
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

    private boolean checkDigits(int value, List<Integer>[] digits) {
        for (int i = 0; i < 3; ++i) {
            digits[i].clear();
        }

        value /= 10;
        int count = 1;
        while (0 != value) {
            int remainder = value % 10;
            if (0 == remainder || 1 == remainder || 2 == remainder) {
                digits[remainder].add(count);
            }
            value /= 10;
            ++count;
        }

        for (List<Integer> digit : digits) {
            if (digit.size() >= 3) {
                return true;
            }
        }
        return false;
    }

    private boolean checkPrimeFamily(int pivot, int target, List<Integer>[] digits, List<Integer> steps, int[] auxiliary) {
        boolean isFamily = false;
        for (int i = 0; i < 3; ++i) {
            if (digits[i].size() < 3) {
                continue;
            }

            steps.clear();
            combination(digits[i], 0, 3, digits[i].size(), steps, auxiliary, 0);
            for (int step : steps) {
                int count = 10 - target - i;
                int value = pivot;
                for (int j = i; j < 9; ++j) {
                    value += step;
                    if (!isPrime(value)) {
                        --count;
                    }
                    if (count < 0) {
                        break;
                    }
                }
                isFamily = (0 == count);
            }
        }
        return isFamily;
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

    private void combination(List<Integer> digits, int index, int count, int length, List<Integer> steps, int[] auxiliary, int size) {
        if (count == size) {
            int value = 0;
            for (int digit : auxiliary) {
                value += digit;
            }
            steps.add(value);
            return;
        }

        for (int i = index; i < length; ++i) {
            auxiliary[size] = (int) Math.pow(10, digits.get(i));
            ++size;
            combination(digits, i + 1, count, length, steps, auxiliary, size);
            --size;
        }
    }
}

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
        List<Integer> auxiliary = new ArrayList<>();

        int index = 1111;
        while (true) {
            int prime = getNextPrime(index);
            if (checkDigits(prime, digits) && checkPrimeFamily(prime, target, digits, steps, auxiliary)) {
                System.out.println(prime);
                return;
            }
            index = prime + 1;
        }
    }

    private int getNextPrime(int value) {
        if (0 == (value & 1)) {
            ++value;
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

    private boolean checkPrimeFamily(int pivot, int target, List<Integer>[] digits, List<Integer> steps, List<Integer> auxiliary) {
        boolean isFamily = false;
        for (int i = 0; i < 3; ++i) {
            if (digits[i].size() < 3) {
                continue;
            }

            steps.clear();
            auxiliary.clear();
            combination(digits[i], 0, 3, digits[i].size(), steps, auxiliary);
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
        if (0 == (value & 1)) {
            return 2 == value;
        }

        int border = (int) Math.sqrt(value);
        for (int i = 3; i <= border; i += 2) {
            if (0 == value % i) {
                return false;
            }
        }
        return 1 != value;
    }

    private void combination(List<Integer> digits, int start, int count, int length, List<Integer> steps, List<Integer> auxiliary) {
        if (count == auxiliary.size()) {
            int value = 0;
            for (int digit : auxiliary) {
                value += digit;
            }
            steps.add(value);
            return;
        }

        for (int i = start; i < length; ++i) {
            auxiliary.add((int) Math.pow(10, digits.get(i)));
            combination(digits, i + 1, count, length, steps, auxiliary);
            auxiliary.remove(auxiliary.size() - 1);
        }
    }
}

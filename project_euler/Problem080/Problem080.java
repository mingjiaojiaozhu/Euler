package project_euler;

import java.util.Arrays;

public class Problem080 {
    public void solution() {
        int target = 100;
        Decimal current = new Decimal(100, 0);
        Decimal auxiliary = new Decimal(100, 0);
        int length = (target + 2) / 5 + 1;
        int pivot = (int) Math.pow(10, (target + 2) % 5);
        int result = 0;
        for (int i = 2; i <= target; ++i) {
            if (Math.abs(Math.floor(Math.sqrt(i) + 0.5) - Math.sqrt(i)) > 0.00000001) {
                getDigits(i, current, auxiliary, length, pivot);
                result += getSummation(current);
            }
        }
        System.out.println(result);
    }

    private void getDigits(int value, Decimal current, Decimal auxiliary, int length, int pivot) {
        setValue(5, current);
        setValue(value * 5, auxiliary);
        while (checkLength(current, length, pivot)) {
            if (!isGreater(current, auxiliary)) {
                getDifference(current, auxiliary);
                current.value[0] += 10;
                carry(current);
            } else {
                getProduct(auxiliary, 100);
                fillZero(current);
            }
        }
    }

    private int getSummation(Decimal current) {
        int result = addDigit(current.value[0] / (int) 1e3);
        for (int i = 1; i < current.length; i++) {
            result += addDigit(current.value[i]);
        }
        return result;
    }

    private void setValue(int value, Decimal decimal) {
        Arrays.fill(decimal.value, 0);
        decimal.value[0] = value;
        decimal.length = 1;
    }

    private boolean checkLength(Decimal current, int length, int pivot) {
        if (current.length < length) {
            return true;
        }
        return current.value[length - 1] < pivot;
    }

    private boolean isGreater(Decimal current, Decimal pivot) {
        if (current.length != pivot.length) {
            return current.length > pivot.length;
        }

        for (int i = current.length - 1; i >= 0; --i) {
            if (current.value[i] != pivot.value[i]) {
                return current.value[i] > pivot.value[i];
            }
        }
        return false;
    }

    private void getDifference(Decimal decimal, Decimal difference) {
        for (int i = 0; i < decimal.length; ++i) {
            difference.value[i] -= decimal.value[i];
        }

        for (int i = 0; i < difference.length; ++i) {
            if (difference.value[i] < 0) {
                --difference.value[i + 1];
                difference.value[i] += (int) 1e5;
            }
        }
        while (0 == difference.value[difference.length - 1]) {
            --difference.length;
        }
    }

    private void getProduct(Decimal decimal, int factor) {
        for (int i = 0; i < decimal.length; ++i) {
            decimal.value[i] *= factor;
        }
        carry(decimal);
    }

    private void fillZero(Decimal decimal) {
        int remainder = decimal.value[0] % 10;
        decimal.value[0] -= remainder;
        getProduct(decimal, 10);
        decimal.value[0] += remainder;
    }

    private void carry(Decimal decimal) {
        for (int i = 0; i < decimal.length; ++i) {
            if (decimal.value[i] >= (int) 1e5) {
                decimal.value[i + 1] += decimal.value[i] / (int) 1e5;
                decimal.value[i] %= (int) 1e5;
            }
        }
        if (0 != decimal.value[decimal.length]) {
            ++decimal.length;
        }
    }

    private int addDigit(int value) {
        int result = 0;
        while (0 != value) {
            result += value % 10;
            value /= 10;
        }
        return result;
    }

    private static class Decimal {
        public int[] value;
        public int length;

        public Decimal(int capacity, int length) {
            this.value = new int[capacity];
            Arrays.fill(this.value, 0);
            this.length = length;
        }
    }
}

package project_euler;

import java.util.Arrays;

public class Problem065 {
    public void solution() {
        int target = 100;
        Decimal previous = new Decimal(100, 0);
        Decimal current = new Decimal(100, 0);
        setValue(1, previous);
        setValue(2, current);
        for (int i = 2; i <= target; ++i) {
            int factor = 1;
            if (0 == i % 3) {
                factor = (i << 1) / 3;
            }
            getSummation(current, factor, previous);
            swapDecimal(previous, current);
        }

        int result = 0;
        for (int i = 0; i < current.length; ++i) {
            int value = current.value[i];
            while (0 != value) {
                result += value % 10;
                value /= 10;
            }
        }
        System.out.println(result);
    }

    private void setValue(int value, Decimal decimal) {
        decimal.value[0] = value;
        decimal.length = 1;
    }

    private void getSummation(Decimal decimal, int factor, Decimal summation) {
        for (int i = 0; i < decimal.length; ++i) {
            summation.value[i] += decimal.value[i] * factor;
        }

        for (int i = 0; i < summation.length; ++i) {
            if (summation.value[i] >= (int) 1e5) {
                summation.value[i + 1] += summation.value[i] / (int) 1e5;
                summation.value[i] %= (int) 1e5;
            }
        }
        if (0 != summation.value[summation.length]) {
            ++summation.length;
        }
    }

    private void swapDecimal(Decimal previous, Decimal current) {
        int length = Math.max(previous.length, current.length);
        for (int i = 0; i < length; ++i) {
            previous.value[i] ^= current.value[i];
            current.value[i] ^= previous.value[i];
            previous.value[i] ^= current.value[i];
        }
        previous.length ^= current.length;
        current.length ^= previous.length;
        previous.length ^= current.length;
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

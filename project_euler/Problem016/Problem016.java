package project_euler;

import java.util.Arrays;

public class Problem016 {
    public void solution() {
        int target = 1000;
        int length = (target + 4) / 5;
        Decimal decimal = new Decimal(length, 0);
        int[] auxiliary = new int[length];
        getPower(target, decimal, auxiliary);

        int result = 0;
        for (int i = 0; i < decimal.length; ++i) {
            int value = decimal.value[i];
            while (value > 0) {
                result += value % 10;
                value /= 10;
            }
        }
        System.out.println(result);
    }

    private void getPower(int value, Decimal decimal, int[] auxiliary) {
        if (value < 8) {
            decimal.value[0] = (int) Math.pow(2, value);
            decimal.length = 1;
            return;
        }

        getPower(value >> 1, decimal, auxiliary);
        getSquare(decimal, auxiliary);
        if (0 != (value & 1)) {
            getDouble(decimal);
        }
    }

    private void getSquare(Decimal decimal, int[] auxiliary) {
        Arrays.fill(auxiliary, 0);
        for (int i = 0; i < decimal.length; ++i) {
            for (int j = 0; j < decimal.length; ++j) {
                long result = (long) decimal.value[i] * decimal.value[j];
                int index = i + j;
                auxiliary[index] += (int) (result % (int) 1e5);
                auxiliary[index + 1] += (int) (result / (int) 1e5);
            }
        }

        decimal.length = (decimal.length << 1) - 1;
        for (int i = 0; i < decimal.length; ++i) {
            if (auxiliary[i] >= (int) 1e5) {
                auxiliary[i + 1] += auxiliary[i] / (int) 1e5;
                auxiliary[i] %= (int) 1e5;
            }
        }
        if (0 != auxiliary[decimal.length]) {
            ++decimal.length;
        }
        System.arraycopy(auxiliary, 0, decimal.value, 0, decimal.length);
    }

    private void getDouble(Decimal decimal) {
        for (int i = 0; i < decimal.length; ++i) {
            decimal.value[i] <<= 1;
        }

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

package project_euler;

import java.util.Arrays;

public class Problem056 {
    public void solution() {
        int target = 100;
        Decimal decimal = new Decimal(target, 0);
        int result = 0;
        for (int i = 2; i < target; ++i) {
            Arrays.fill(decimal.value, 0);
            setValue(i, decimal);
            for (int j = 2; j < target; ++j) {
                getProduct(i, decimal);
                result = getDigital(decimal, result);
            }
        }
        System.out.println(result);
    }

    private void setValue(int value, Decimal decimal) {
        decimal.value[0] = value;
        decimal.length = 1;
    }

    private void getProduct(int value, Decimal decimal) {
        for (int i = 0; i < decimal.length; ++i) {
            decimal.value[i] *= value;
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

    private int getDigital(Decimal decimal, int pivot) {
        int result = 0;
        for (int i = 0; i < decimal.length; ++i) {
            int value = decimal.value[i];
            while (0 != value) {
                result += value % 10;
                value /= 10;
            }
        }
        return Math.max(result, pivot);
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

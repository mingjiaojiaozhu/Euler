package project_euler;

import java.util.Arrays;

public class Problem020 {
    public void solution() {
        int target = 100;
        Decimal decimal = new Decimal(target, 0);
        decimal.value[0] = target;
        decimal.length = 1;

        for (int i = target - 1; i > 1; --i) {
            getProduct(i, decimal);
        }

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

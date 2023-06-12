package project_euler;

import java.util.Arrays;

public class Problem055 {
    public void solution() {
        int target = 10000;
        Decimal decimal = new Decimal(100, 0);
        int[] auxiliary = new int[100];
        int result = 0;
        for (int i = 1; i < target; ++i) {
            if (isLychrel(i, decimal, auxiliary)) {
                ++result;
            }
        }
        System.out.println(result);
    }

    private boolean isLychrel(int value, Decimal decimal, int[] auxiliary) {
        setValue(value, decimal);
        reverseValue(decimal, auxiliary);
        getSummation(decimal, auxiliary);
        
        int count = 0;
        while (count < 50) {
            reverseValue(decimal, auxiliary);
            if (isEqual(decimal, auxiliary)) {
                return false;
            }
            getSummation(decimal, auxiliary);
            ++count;
        }
        return true;
    }

    private void setValue(int value, Decimal decimal) {
        Arrays.fill(decimal.value, 0);
        decimal.length = 0;
        while (0 != value) {
            decimal.value[decimal.length] = value % (int) 1e5;
            ++decimal.length;
            value /= (int) 1e5;
        }
    }

    private void reverseValue(Decimal decimal, int[] auxiliary) {
        Arrays.fill(auxiliary, 0);
        int index = 0;
        int count = 0;
        for (int i = decimal.length - 1; i >= 0; --i) {
            int value = decimal.value[i];
            int divisor = (int) 1e5 / 10;
            if (i == decimal.length - 1) {
                while (0 == value / divisor) {
                    divisor /= 10;
                }
            }
            while (0 != divisor) {
                auxiliary[index] += (value / divisor) * (int) Math.pow(10, count);
                value %= divisor;
                divisor /= 10;
                ++count;
                if (5 == count) {
                    ++index;
                    count = 0;
                }
            }
        }
    }

    private void getSummation(Decimal decimal, int[] auxiliary) {
        for (int i = 0; i < decimal.length; ++i) {
            decimal.value[i] += auxiliary[i];
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

    private boolean isEqual(Decimal decimal, int[] auxiliary) {
        for (int i = 0; i < decimal.length; ++i) {
            if (decimal.value[i] != auxiliary[i]) {
                return false;
            }
        }
        return true;
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

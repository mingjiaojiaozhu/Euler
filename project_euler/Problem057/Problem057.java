package project_euler;

import java.util.Arrays;

public class Problem057 {
    public void solution() {
        int target = 1000;
        Decimal numerator = new Decimal(100, 0);
        Decimal denominator = new Decimal(100, 0);
        setValue(3, numerator);
        setValue(2, denominator);

        int result = 0;
        for (int i = 2; i < target; ++i) {
            getSummation(denominator, numerator);
            getSummation(numerator, denominator);
            swapDecimal(numerator, denominator);
            if (numerator.length > denominator.length || getDigits(numerator.value[numerator.length - 1]) > getDigits(denominator.value[denominator.length - 1])) {
                ++result;
            }
        }
        System.out.println(result);
    }

    private void setValue(int value, Decimal decimal) {
        decimal.value[0] = value;
        decimal.length = 1;
    }

    private void getSummation(Decimal decimal, Decimal summation) {
        for (int i = 0; i < decimal.length; ++i) {
            summation.value[i] += decimal.value[i];
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

    private void swapDecimal(Decimal numerator, Decimal denominator) {
        int length = Math.max(numerator.length, denominator.length);
        for (int i = 0; i < length; ++i) {
            numerator.value[i] ^= denominator.value[i];
            denominator.value[i] ^= numerator.value[i];
            numerator.value[i] ^= denominator.value[i];
        }
        numerator.length ^= denominator.length;
        denominator.length ^= numerator.length;
        numerator.length ^= denominator.length;
    }

    private int getDigits(int value) {
        int result = 0;
        while (0 != value) {
            ++result;
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

package project_euler;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Problem066 {
    public void solution() {
        int target = 1000;
        List<Integer> factors = new ArrayList<>();
        Decimal previous = new Decimal(100, 0);
        Decimal current = new Decimal(100, 0);
        Decimal auxiliary = new Decimal(100, 0);

        int result = 0;
        Decimal pivot = new Decimal(100, 0);
        for (int i = 5; i <= target; ++i) {
            if (getSolution(i, factors, previous, current, auxiliary) && isGreater(current, pivot)) {
                swapDecimal(current, pivot);
                result = i;
            }
        }
        System.out.println(result);
    }

    private boolean getSolution(int value, List<Integer> factors, Decimal previous, Decimal current, Decimal auxiliary) {
        factors.clear();
        int start = getPeriod(value, factors);
        if (0 == start) {
            return false;
        }

        setValue(0, previous);
        setValue(1, current);
        getConvergents(previous, current, factors);
        if (0 != (factors.size() & 1)) {
            return true;
        }

        setValue(1, previous);
        setValue(start, auxiliary);
        getConvergents(previous, auxiliary, factors);
        swapDecimal(previous, current);
        getProduct(previous, auxiliary, current);
        getDouble(current);
        return true;
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

    private int getPeriod(int value, List<Integer> factors) {
        if (Math.abs(Math.floor(Math.sqrt(value) + 0.5) - Math.sqrt(value)) < 0.00000001) {
            return 0;
        }

        int initial = (int) Math.sqrt(value);
        int pivot = initial << 1;
        int current = initial;
        int offset = 0;
        int factor = 1;
        while (current != pivot) {
            offset = current * factor - offset;
            factor = (value - offset * offset) / factor;
            current = (initial + offset) / factor;
            factors.add(current);
        }
        factors.remove(factors.size() - 1);
        return initial;
    }

    private void setValue(int value, Decimal decimal) {
        Arrays.fill(decimal.value, 0);
        decimal.value[0] = value;
        decimal.length = 1;
    }

    private void getConvergents(Decimal previous, Decimal current, List<Integer> factors) {
        for (int factor : factors) {
            getSummation(current, factor, previous);
            swapDecimal(previous, current);
        }
    }

    private void getProduct(Decimal multiplicand, Decimal multiplier, Decimal product) {
        for (int i = 0; i < multiplicand.length; ++i) {
            for (int j = 0; j < multiplier.length; ++j) {
                long value = (long) multiplicand.value[i] * multiplier.value[j];
                int index = i + j;
                product.value[index] += (int) (value % (int) 1e5);
                product.value[index + 1] += (int) (value / (int) 1e5);
            }
        }
        product.length = multiplicand.length + multiplier.length - 1;
        carry(product);
    }

    private void getDouble(Decimal decimal) {
        for (int i = 0; i < decimal.length; ++i) {
            decimal.value[i] <<= 1;
        }
        carry(decimal);
    }

    private void getSummation(Decimal decimal, int factor, Decimal summation) {
        for (int i = 0; i < decimal.length; ++i) {
            summation.value[i] += decimal.value[i] * factor;
        }
        carry(summation);
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

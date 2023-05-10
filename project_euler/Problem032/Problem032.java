package project_euler;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class Problem032 {
    public void solution() {
        boolean[] digits = new boolean[9];
        Set<Integer> products = new HashSet<>();
        for (int i = 1; i < 10; ++i) {
            for (int j = 10000 / i; j >= 1234; --j) {
                getProducts(i, j, digits, products);
            }
        }

        for (int i = 10; i < 100; ++i) {
            for (int j = 10000 / i; j >= 123; --j) {
                getProducts(i, j, digits, products);
            }
        }

        int result = 0;
        for (int product : products) {
            result += product;
        }
        System.out.println(result);
    }

    private void getProducts(int multiplicand, int multiplier, boolean[] digits, Set<Integer> products) {
        Arrays.fill(digits, false);
        if (isPandigital(multiplicand, digits) && isPandigital(multiplier, digits)) {
            int product = multiplicand * multiplier;
            if (isPandigital(product, digits)) {
                products.add(product);
            }
        }
    }

    private boolean isPandigital(int value, boolean[] digits) {
        while (0 != value) {
            int index = value % 10 - 1;
            if (index < 0 || digits[index]) {
                return false;
            }
            digits[index] = true;
            value /= 10;
        }
        return true;
    }
}

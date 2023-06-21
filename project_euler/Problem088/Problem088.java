package project_euler;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class Problem088 {
    public void solution() {
        int target = 12000;
        int length = (int) Math.ceil(Math.log(target) / Math.log(2));
        int[] products = new int[target - 1];
        Arrays.fill(products, (int) Math.pow(2, length + 1));

        int[] digits = new int[length];
        Arrays.fill(digits, 1);
        digits[0] = 2;
        digits[1] = 2;

        int pivot = target - length;
        while (true) {
            int product = 1;
            int summation = 0;
            for (int value : digits) {
                product *= value;
                summation += value;
            }
            int difference = product - summation;
            if (difference <= pivot) {
                int index = difference + length - 2;
                if (index >= 0 && products[index] > product) {
                    products[index] = product;
                }
                ++digits[0];
            } else {
                if (!carry(digits, length)) {
                    break;
                }
            }
        }

        int result = 0;
        Set<Integer> auxiliary = new HashSet<>();
        for (int value : products) {
            if (!auxiliary.contains(value)) {
                result += value;
                auxiliary.add(value);
            }
        }
        System.out.println(result);
    }

    private boolean carry(int[] digits, int length) {
        for (int i = 1; i < length; ++i) {
            if (digits[i] != digits[i - 1]) {
                ++digits[i];
                int value = digits[i];
                for (int j = 0; j < i; ++j) {
                    digits[j] = value;
                }
                return true;
            }
        }
        return false;
    }
}

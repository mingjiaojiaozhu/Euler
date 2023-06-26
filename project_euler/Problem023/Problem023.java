package project_euler;

import java.util.HashSet;
import java.util.Set;

public class Problem023 {
    public void solution() {
        int start = 24;
        int end = 28123;
        Set<Integer> abundants = new HashSet<>();
        for (int i = start >> 1; i <= start; ++i) {
            if (isAbundant(i)) {
                abundants.add(i);
            }
        }

        int result = start * (start - 1) >> 1;
        for (int i = start + 1; i <= end; ++i) {
            boolean isNonAbundant = true;
            for (int abundant : abundants) {
                if (abundants.contains(i - abundant)) {
                    isNonAbundant = false;
                    break;
                }
            }
            if (isNonAbundant) {
                result += i;
            }

            if (isAbundant(i)) {
                abundants.add(i);
            }
        }
        System.out.println(result);
    }

    private boolean isAbundant(int value) {
        int border = (int) Math.sqrt(value);
        int summation = 1;
        for (int i = 2; i < border; ++i) {
            if (0 == value % i) {
                summation += i + value / i;
            }
        }
        if (0 == value % border) {
            summation += border;
            if (value != border * border) {
                summation += value / border;
            }
        }
        return summation > value;
    }
}

package project_euler;

import java.util.HashSet;
import java.util.Set;

public class Problem092 {
    public void solution() {
        int target = 10000000;
        int border = 9 * 9 * (int) Math.log10(target);
        Set<Integer> chains = new HashSet<>();
        int pivot = 89;
        chains.add(pivot);

        int[] squares = new int[10];
        for (int i = 0; i < 10; ++i) {
            squares[i] = i * i;
        }

        int result = 0;
        for (int i = 1; i <= border; ++i) {
            if (getChains(i, chains, pivot, squares)) {
                ++result;
            }
        }
        for (int i = border + 1; i < target; ++i) {
            if (chains.contains(squareDigits(i, squares))) {
                ++result;
            }
        }
        System.out.println(result);
    }

    private boolean getChains(int value, Set<Integer> chains, int pivot, int[] squares) {
        if (chains.contains(value) || pivot == value) {
            return true;
        }
        if (1 == value) {
            return false;
        }

        boolean result = getChains(squareDigits(value, squares), chains, pivot, squares);
        if (result) {
            chains.add(value);
        }
        return result;
    }

    private int squareDigits(int value, int[] squares) {
        int result = 0;
        while (0 != value) {
            result += squares[value % 10];
            value /= 10;
        }
        return result;
    }
}

package project_euler;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class Problem074 {
    public void solution() {
        int target = 60;
        int border = 1000000;
        int step = (int) Math.log10(border);
        List<Integer> permutations = new ArrayList<>();
        for (int i = 1; i < 10; ++i) {
            permutations.add(i);
        }
        Set<Integer> chains = new HashSet<>();
        Map<Integer, Integer> terms = new HashMap<>();
        int[] factorials = new int[10];
        factorials[0] = 1;
        for (int i = 1; i < 10; ++i) {
            factorials[i] = factorials[i - 1] * i;
        }
        int[] counts = new int[10];
        List<Integer> auxiliary = new ArrayList<>();
        int result = 0;
        for (int value : permutations) {
            if (target == getTerms(value, chains, terms, factorials, counts)) {
                result += getPermutations(value, factorials, counts);
            }
        }
        for (int i = 1; i < step; ++i) {
            getDigits(permutations, auxiliary);
            for (int value : permutations) {
                if (target == getTerms(value, chains, terms, factorials, counts)) {
                    result += getPermutations(value, factorials, counts);
                }
            }
        }
        System.out.println(result);
    }

    private int getTerms(int value, Set<Integer> chains, Map<Integer, Integer> terms, int[] factorials, int[] counts) {
        chains.clear();
        int pivot = value;
        int result;
        while (true) {
            if (terms.containsKey(value)) {
                result = chains.size() + terms.get(value);
                break;
            }
            if (chains.contains(value)) {
                result = chains.size();
                break;
            }

            chains.add(value);
            value = getSummation(value, factorials, counts);
        }
        terms.put(pivot, result);
        return result;
    }

    private int getPermutations(int value, int[] factorials, int[] counts) {
        int length = 0;
        boolean exists0 = false;
        Arrays.fill(counts, 0);
        while (0 != value) {
            ++length;
            int remainder = value % 10;
            if (0 == remainder) {
                exists0 = true;
            }
            ++counts[remainder];
            value /= 10;
        }

        int result = factorials[length];
        if (exists0) {
            result = result * (length - 1) / length;
        }
        for (int count : counts) {
            if (1 != count) {
                result /= factorials[count];
            }
        }
        return result;
    }

    private void getDigits(List<Integer> permutations, List<Integer> auxiliary) {
        auxiliary.addAll(permutations);
        permutations.clear();
        for (int value : auxiliary) {
            int remainder = value % 10;
            for (int i = 0; i <= remainder; ++i) {
                permutations.add(value * 10 + i);
            }
        }
        auxiliary.clear();
    }

    private int getSummation(int value, int[] factorials, int[] counts) {
        int result = 0;
        while (0 != value) {
            result += factorials[value % 10];
            value /= 10;
        }

        Arrays.fill(counts, 0);
        while (0 != result) {
            ++counts[9 - result % 10];
            result /= 10;
        }

        for (int i = 0; i < 10; ++i) {
            int count = counts[i];
            for (int j = 0; j < count; ++j) {
                result = result * 10 + 9 - i;
            }
        }
        return result;
    }
}

package project_euler;

import java.util.HashMap;
import java.util.Map;

public class Problem073 {
    public void solution() {
        int target = 12000;
        Map<Integer, Integer> fractions = new HashMap<>();
        fractions.put(1, getCount(1));
        int result = getFractions(target, fractions) - fractions.get(1);
        System.out.println(result);
    }

    private int getFractions(int target, Map<Integer, Integer> fractions) {
        if (fractions.containsKey(target)) {
            return fractions.get(target);
        }

        int index = 2;
        int result = 0;
        while (index <= target) {
            int step = target / (target / index);
            result += (step - index + 1) * getFractions(target / step, fractions);
            index = step + 1;
        }
        result = getCount(target) - result;
        fractions.put(target, result);
        return result;
    }

    private int getCount(int value) {
        int quotient = value / 6;
        int remainder = value % 6;
        if (5 == remainder) {
            return quotient * (quotient * 3 - 2 + remainder) + 1;
        }
        return quotient * (quotient * 3 - 2 + remainder);
    }
}

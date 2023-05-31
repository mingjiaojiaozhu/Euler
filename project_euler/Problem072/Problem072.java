package project_euler;

import java.util.HashMap;
import java.util.Map;

public class Problem072 {
    public void solution() {
        int target = 1000000;
        Map<Integer, Long> fractions = new HashMap<>();
        fractions.put(1, getSummation(1));
        long result = getFractions(target, fractions) - fractions.get(1);
        System.out.println(result);
    }

    private long getFractions(int target, Map<Integer, Long> fractions) {
        if (fractions.containsKey(target)) {
            return fractions.get(target);
        }

        int index = 2;
        long result = 0L;
        while (index <= target) {
            int step = target / (target / index);
            result += (step - index + 1) * getFractions(target / step, fractions);
            index = step + 1;
        }
        result = getSummation(target) - result;
        fractions.put(target, result);
        return result;
    }

    private long getSummation(int value) {
        return (long) value * (value + 1) >> 1;
    }
}

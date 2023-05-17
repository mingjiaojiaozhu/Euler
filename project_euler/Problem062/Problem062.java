package project_euler;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Problem062 {
    public void solution() {
        int target = 5;
        Map<Long, List<Long>> cubes = new HashMap<>();
        int index = 5;
        int pivot = 0;
        while (true) {
            long value = (long) Math.pow(index, 3);
            long summation = getSummation(value);
            int digit = (int) Math.log10(value);
            if (pivot != digit) {
                cubes.clear();
                pivot = digit;
            } else {
                if (cubes.containsKey(summation) && cubes.get(summation).size() == target - 1) {
                    System.out.println(cubes.get(summation).get(0));
                    return;
                }
            }
            if (!cubes.containsKey(summation)) {
                cubes.put(summation, new ArrayList<>());
            }
            cubes.get(summation).add(value);
            ++index;
        }
    }

    private long getSummation(long value) {
        long result = 0L;
        while (0L != value) {
            result += (long) Math.pow(10, value % 10);
            value /= 10;
        }
        return result;
    }
}

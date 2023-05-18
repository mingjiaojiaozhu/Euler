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
            long digits = getDigits(value);
            int count = (int) Math.log10(value);
            if (pivot != count) {
                cubes.clear();
                pivot = count;
            } else {
                if (cubes.containsKey(digits) && cubes.get(digits).size() == target - 1) {
                    System.out.println(cubes.get(digits).get(0));
                    return;
                }
            }
            if (!cubes.containsKey(digits)) {
                cubes.put(digits, new ArrayList<>());
            }
            cubes.get(digits).add(value);
            ++index;
        }
    }

    private long getDigits(long value) {
        long result = 0L;
        while (0L != value) {
            result += (long) Math.pow(10, value % 10);
            value /= 10;
        }
        return result;
    }
}

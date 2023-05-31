package project_euler;

import java.util.HashMap;
import java.util.Map;

public class Problem075 {
    public void solution() {
        int target = 1500000;
        int border = (int) Math.sqrt(target >> 1);
        Map<Integer, Integer> perimeters = new HashMap<>();
        for (int i = 2; i <= border; ++i) {
            for (int j = 1; j < i; ++j) {
                if (0 != ((i + j) & 1) && isRelativelyPrime(i, j)) {
                    int pivot = i * (i + j) << 1;
                    int length = pivot;
                    while (length < target) {
                        perimeters.put(length, perimeters.getOrDefault(length, 0) + 1);
                        length += pivot;
                    }
                }
            }
        }

        int result = 0;
        for (Map.Entry<Integer, Integer> entry : perimeters.entrySet()) {
            if (1 == entry.getValue()) {
                ++result;
            }
        }
        System.out.println(result);
    }

    private boolean isRelativelyPrime(int i, int j) {
        while (0 != i % j) {
            int auxiliary = i % j;
            i = j;
            j = auxiliary;
        }
        return 1 == j;
    }
}

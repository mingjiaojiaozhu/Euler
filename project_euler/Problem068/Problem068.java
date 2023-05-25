package project_euler;

import java.util.ArrayList;
import java.util.List;

public class Problem068 {
    public void solution() {
        int target = 10;
        List<Integer> ring = new ArrayList<>();
        int border = target >> 1;
        int start = border + 1;
        ring.add(start);
        ring.add(border);
        int summation = ((target * (target + 1) >> 1) + (border * (border + 1) >> 1)) / border;
        int pivot = summation - border - start;
        ring.add(pivot);
        for (int i = target; i > start; --i) {
            ring.add(i);
            ring.add(pivot);
            pivot = summation - pivot - i;
            ring.add(pivot);
        }

        long result = 0L;
        for (int value : ring) {
            if (value >= 10) {
                result = result * 100 + value;
            } else {
                result = result * 10 + value;
            }
        }
        System.out.println(result);
    }
}

package project_euler;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Problem029 {
    public void solution() {
        int start = 2;
        int end = 100;
        List<Double> terms = new ArrayList<>();
        for (int i = start; i <= end; ++i) {
            for (int j = start; j <= end; ++j) {
                terms.add(i * Math.log(j));
            }
        }

        Collections.sort(terms);

        int result = terms.size();
        for (int i = result - 1; i >= 1; --i) {
            if (Math.abs(terms.get(i) - terms.get(i - 1)) < 0.00000001) {
                --result;
            }
        }
        System.out.println(result);
    }
}

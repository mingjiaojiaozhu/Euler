package project_euler;

import java.util.ArrayList;
import java.util.List;

public class Problem044 {
    public void solution() {
        List<Integer> pentagons = new ArrayList<>();
        int index = 1;
        while (true) {
            int current = index * (3 * index - 1) >> 1;
            for (int pentagon : pentagons) {
                if (isPentagon(current + pentagon) && isPentagon(current - pentagon)) {
                    System.out.println(current - pentagon);
                    return;
                }
            }
            pentagons.add(current);
            ++index;
        }
    }

    private boolean isPentagon(int value) {
        double auxiliary = Math.sqrt(value * 24 + 1);
        return Math.abs(Math.floor(auxiliary + 0.5) - auxiliary) < 0.00000001 && 0 == ((int) auxiliary + 1) % 6;
    }
}

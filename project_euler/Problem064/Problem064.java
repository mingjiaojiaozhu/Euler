package project_euler;

public class Problem064 {
    public void solution() {
        int target = 10000;
        int result = 0;
        for (int i = 1; i <= target; ++i) {
            if (0 != (getPeriod(i) & 1)) {
                ++result;
            }
        }
        System.out.println(result);
    }

    private int getPeriod(int value) {
        double auxiliary = Math.sqrt(value);
        if (Math.abs(Math.floor(auxiliary + 0.5) - auxiliary) < 0.00000001) {
            return 0;
        }

        int initial = (int) auxiliary;
        int pivot = initial << 1;
        int current = initial;
        int offset = 0;
        int factor = 1;
        int count = 0;
        while (current != pivot) {
            offset = current * factor - offset;
            factor = (value - offset * offset) / factor;
            current = (initial + offset) / factor;
            ++count;
        }
        return count;
    }
}

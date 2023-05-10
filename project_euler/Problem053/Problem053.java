package project_euler;

public class Problem053 {
    public void solution() {
        int target = 1000000;
        int result = 0;
        for (int i = 23; i <= 100; ++i) {
            result += i + 1 - (getIndex(i, target) << 1);
        }
        System.out.println(result);
    }

    private int getIndex(int value, int target) {
        int start = 0;
        int end = (value + 1) >> 1;
        while (start <= end) {
            int current = start + ((end - start) >> 1);
            if (checkCombination(value, current, target)) {
                start = current + 1;
            } else {
                end = current - 1;
            }
        }
        return start;
    }

    private boolean checkCombination(int value, int count, int target) {
        int result = 1;
        for (int i = 0; i < count; ++i) {
            result = result * (value - i) / (i + 1);
            if (result > target) {
                return false;
            }
        }
        return true;
    }
}

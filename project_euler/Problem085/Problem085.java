package project_euler;

public class Problem085 {
    public void solution() {
        int target = 2000000;
        int border = ((int) Math.sqrt(1 + 8 * Math.sqrt(target)) - 1) >> 1;
        int result = 0;
        int pivot = target;
        for (int i = 1; i <= border; ++i) {
            int length = ((int) Math.sqrt(1 + (double) (target << 4) / i / (i + 1)) - 1) >> 1;
            int value = Math.min(Math.abs(getCount(length, i) - target), Math.abs(getCount(length + 1, i) - target));
            if (pivot > value) {
                result = length * i;
                pivot = value;
            }
        }
        System.out.println(result);
    }

    private int getCount(int length, int width) {
        return length * (length + 1) * width * (width + 1) >> 2;
    }
}

package project_euler;

public class Problem094 {
    public void solution() {
        int target = 1000000000;
        int[] index = new int[]{2, 1};
        long result = 0L;
        while (true) {
            int auxiliary = (index[0] << 1) + index[1] * 3;
            index[1] = index[0] + (index[1] << 1);
            index[0] = auxiliary;

            int value = getTriangle(index, -1, target);
            if (-1 == value) {
                break;
            }
            result += value;

            value = getTriangle(index, 1, target);
            if (-1 == value) {
                break;
            }
            result += value;
        }
        System.out.println(result);
    }

    private int getTriangle(int[] index, int offset, int target) {
        int perimeter = (index[0] + offset) << 1;
        if (perimeter >= target) {
            return -1;
        }

        double length = (double) ((index[0] << 1) + offset) / 3;
        if (Math.abs(Math.floor(length + 0.5) - length) > 0.00000001) {
            return 0;
        }
        double area = (length + offset) * index[1] / 2;
        if (Math.abs(Math.floor(area + 0.5) - area) > 0.00000001) {
            return 0;
        }
        return perimeter;
    }
}

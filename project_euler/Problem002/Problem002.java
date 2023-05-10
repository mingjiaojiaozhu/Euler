package project_euler;

public class Problem002 {
    public void solution() {
        int target = 4000000;
        int[] previous = {2, 8};
        int result = previous[0] + previous[1];
        while (true) {
            int current = previous[0] + (previous[1] << 2);
            if (current > target) {
                break;
            }

            result += current;
            previous[0] = previous[1];
            previous[1] = current;
        }
        System.out.println(result);
    }
}

package project_euler;

public class Problem030 {
    public void solution() {
        int target = 5;
        int[] powers = new int[10];
        for (int i = 0; i < 10; ++i) {
            powers[i] = (int) Math.pow(i, target);
        }

        int result = 0;
        for (int i = 6 * powers[9]; i >= 10; --i) {
            if (i == getPowerDigit(i, powers)) {
                result += i;
            }
        }
        System.out.println(result);
    }

    private int getPowerDigit(int value, int[] powers) {
        int result = 0;
        while (0 != value) {
            result += powers[value % 10];
            value /= 10;
        }
        return result;
    }
}

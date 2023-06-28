package project_euler;

public class Problem091 {
    public void solution() {
        int target = 50;
        int result = target * target * 3;
        for (int i = 1; i < target; ++i) {
            for (int j = 1; j <= target; ++j) {
                int divisor = commonDivisor(i, j);
                result += Math.min((target - i) * divisor / j, j * divisor / i) << 1;
            }
        }
        System.out.println(result);
    }

    private int commonDivisor(int i, int j) {
        while (0 != i % j) {
            int auxiliary = i % j;
            i = j;
            j = auxiliary;
        }
        return j;
    }
}

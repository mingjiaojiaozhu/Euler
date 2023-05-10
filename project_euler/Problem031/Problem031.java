package project_euler;

public class Problem031 {
    public void solution() {
        int target = 200;
        int[] coins = new int[]{1, 2, 5, 10, 20, 50, 100, 200};
        int result = getWays(target, coins, coins.length - 1);
        System.out.println(result);
    }

    private int getWays(int target, int[] coins, int index) {
        if (0 == target || 0 == index) {
            return 1;
        }

        if (target < coins[index]) {
            return getWays(target, coins, index - 1);
        }
        return getWays(target, coins, index - 1) + getWays(target - coins[index], coins, index);
    }
}

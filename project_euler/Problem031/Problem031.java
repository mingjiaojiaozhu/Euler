package project_euler;

public class Problem031 {
    public void solution() {
        int target = 200;
        int[] coins = new int[]{1, 2, 5, 10, 20, 50, 100, 200};
        int[] ways = new int[target + 1];
        ways[0] = 1;
        for (int coin : coins) {
            for (int i = coin; i <= target; ++i) {
                ways[i] += ways[i - coin];
            }
        }
        System.out.println(ways[target]);
    }
}

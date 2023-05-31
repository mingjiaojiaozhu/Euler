package project_euler;

import java.util.Arrays;

public class Problem076 {
    public void solution() {
        int target = 100;
        int[] ways = new int[target + 1];
        Arrays.fill(ways, 0);
        ways[0] = 1;
        for (int i = 1; i < target; ++i) {
            for (int j = i; j <= target; ++j) {
                ways[j] += ways[j - i];
            }
        }
        System.out.println(ways[target]);
    }
}

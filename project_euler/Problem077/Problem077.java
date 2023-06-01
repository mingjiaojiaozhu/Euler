package project_euler;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Problem077 {
    public void solution() {
        int target = 5000;
        List<Integer> primes = new ArrayList<>();
        primes.add(2);
        primes.add(3);
        int result = 11;
        while (getWays(result, primes) <= target) {
            ++result;
        }
        System.out.println(result);
    }

    private int getWays(int target, List<Integer> primes) {
        int index = primes.get(primes.size() - 1) + 2;
        while (index <= target) {
            if (isPrime(index)) {
                primes.add(index);
            }
            index += 2;
        }

        int[] ways = new int[target + 1];
        Arrays.fill(ways, 0);
        ways[0] = 1;
        for (int prime : primes) {
            for (int i = prime; i <= target; ++i) {
                ways[i] += ways[i - prime];
            }
        }
        return ways[target];
    }

    private boolean isPrime(int value) {
        if (1 != value % 6 && 5 != value % 6) {
            return 2 == value || 3 == value;
        }

        int border = (int) Math.sqrt(value);
        for (int i = 5; i <= border; i += 6) {
            if (0 == value % i || 0 == value % (i + 2)) {
                return false;
            }
        }
        return 1 != value;
    }
}

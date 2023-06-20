package project_euler;

import java.util.Arrays;

public class Problem010 {
    public void solution() {
        int target = 2000000;
        int length = (target + 1) >> 1;
        boolean[] primes = new boolean[length];
        Arrays.fill(primes, true);
        primes[0] = false;

        int border = (int) Math.sqrt(target);
        for (int i = 3; i <= border; i += 2) {
            if (primes[i >> 1]) {
                for (int j = i * i >> 1; j < length; j += i) {
                    primes[j] = false;
                }
            }
        }

        long result = 2L;
        for (int i = 1; i < length; ++i) {
            if (primes[i]) {
                result += (i << 1) + 1;
            }
        }
        System.out.println(result);
    }
}

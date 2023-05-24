package project_euler;

import java.util.HashSet;
import java.util.Set;

public class Problem046 {
    public void solution() {
        Set<Integer> primes = new HashSet<>();
        primes.add(2);
        int result = 3;
        while (true) {
            if (isPrime(result)) {
                primes.add(result);
            } else {
                int border = (int) Math.sqrt((result - 1) >> 1);
                boolean isGoldbach = false;
                for (int i = 1; i <= border; ++i) {
                    if (primes.contains(result - (i * i << 1))) {
                        isGoldbach = true;
                        break;
                    }
                }
                if (!isGoldbach) {
                    System.out.println(result);
                    return;
                }
            }
            result += 2;
        }
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

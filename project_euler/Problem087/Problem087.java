package project_euler;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Problem087 {
    public void solution() {
        int target = 50000000;
        List<Integer>[] primes = new ArrayList[3];
        for (int i = 0; i < 3; ++i) {
            primes[i] = new ArrayList<>();
        }
        getPrimes(primes, 2, 3);

        int[] borders = new int[]{(int) Math.sqrt(target), (int) Math.pow(target, (double) 1 / 3), (int) Math.pow(target, (double) 1 / 4)};
        int index = 3;
        for (int i = 2; i >= 0; --i) {
            int size = i + 1;
            while (index < borders[i]) {
                if (isPrime(index)) {
                    getPrimes(primes, index, size);
                }
                index += 2;
            }
        }

        Set<Integer> summations = new HashSet<>();
        for (int prime : primes[2]) {
            int pivot = target - prime;
            int border = getIndex(pivot, primes[1]);
            for (int i = 0; i < border; ++i) {
                int value = primes[1].get(i);
                int end = getIndex(pivot - value, primes[0]);
                for (int j = 0; j < end; ++j) {
                    summations.add(prime + value + primes[0].get(j));
                }
            }
        }
        System.out.println(summations.size());
    }

    private void getPrimes(List<Integer>[] primes, int pivot, int size) {
        int value = pivot;
        for (int i = 0; i < size; ++i) {
            value *= pivot;
            primes[i].add(value);
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

    private int getIndex(int value, List<Integer> primes) {
        int start = 0;
        int end = primes.size() - 1;
        while (start <= end) {
            int current = start + ((end - start) >> 1);
            if (primes.get(current) <= value) {
                start = current + 1;
            } else {
                end = current - 1;
            }
        }
        return start;
    }
}

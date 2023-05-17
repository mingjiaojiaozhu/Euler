package project_euler;

import java.util.ArrayList;
import java.util.List;

public class Problem050 {
    public void solution() {
        int target = 1000000;
        List<Integer> primes = new ArrayList<>();
        primes.add(2);
        int index = 3;
        int summation = 2;
        while (summation < target) {
            if (isPrime(index)) {
                primes.add(index);
                summation += index;
            }
            index += 2;
        }

        int length = primes.size();
        for (int i = length - 1; i > 0; --i) {
            int value = summation - primes.get(i);
            if (isPrime(value)) {
                System.out.println(value);
                return;
            }
            summation = value;

            for (int j = i; j < length; ++j) {
                value += primes.get(j) - primes.get(j - i);
                if (isPrime(value) && value < target) {
                    System.out.println(value);
                    return;
                }
            }
        }
    }

    private boolean isPrime(int value) {
        if (0 == (value & 1)) {
            return 2 == value;
        }

        int border = (int) Math.sqrt(value);
        for (int i = 3; i <= border; i += 2) {
            if (0 == value % i) {
                return false;
            }
        }
        return 1 != value;
    }
}

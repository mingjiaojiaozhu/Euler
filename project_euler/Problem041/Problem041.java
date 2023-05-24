package project_euler;

public class Problem041 {
    public void solution() {
        int[] elements = new int[]{7, 6, 5, 4, 3, 2, 1};
        long result = permutation(elements, 0, elements.length, 0L);
        System.out.println(result);
    }

    private long permutation(int[] elements, int index, int length, long pivot) {
        if (index == length) {
            long result = 0L;
            for (int element : elements) {
                result = result * 10 + element;
            }
            if (isPrime(result)) {
                return Math.max(result, pivot);
            }
            return pivot;
        }

        long result = permutation(elements, index + 1, length, pivot);
        for (int i = index + 1; i < length; ++i) {
            swap(elements, index, i);
            result = permutation(elements, index + 1, length, result);
            swap(elements, index, i);
        }
        return result;
    }

    private boolean isPrime(long value) {
        if (1 != value % 6 && 5 != value % 6) {
            return 2 == value || 3 == value;
        }

        long border = (long) Math.sqrt(value);
        for (long i = 5L; i <= border; i += 6) {
            if (0 == value % i || 0 == value % (i + 2)) {
                return false;
            }
        }
        return 1 != value;
    }

    private static void swap(int[] arrays, int i, int j) {
        arrays[i] ^= arrays[j];
        arrays[j] ^= arrays[i];
        arrays[i] ^= arrays[j];
    }
}

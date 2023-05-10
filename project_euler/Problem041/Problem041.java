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
        if (0 == (value & 1)) {
            return 2L == value;
        }

        long border = (long) Math.sqrt(value);
        for (long i = 3L; i <= border; i += 2) {
            if (0 == value % i) {
                return false;
            }
        }
        return 1L != value;
    }

    private static void swap(int[] arrays, int i, int j) {
        arrays[i] ^= arrays[j];
        arrays[j] ^= arrays[i];
        arrays[i] ^= arrays[j];
    }
}

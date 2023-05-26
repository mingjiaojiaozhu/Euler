package project_euler;

import java.util.Arrays;

public class Problem043 {
    public void solution() {
        int[] elements = new int[10];
        elements[5] = 5;
        boolean[] digits = new boolean[10];
        Arrays.fill(digits, false);
        digits[5] = true;

        int start = 500;
        while (0 != start % 11) {
            ++start;
        }

        long result = 0L;
        for (int i = start; i < 600; i += 11) {
            elements[6] = (i % 100) / 10;
            elements[7] = i % 10;
            if (5 != elements[6] && 5 != elements[7] && elements[6] != elements[7]) {
                digits[elements[6]] = true;
                digits[elements[7]] = true;
                result += check13(elements, elements[6] * 100 + elements[7] * 10, digits);
                digits[elements[6]] = false;
                digits[elements[7]] = false;
            }
        }
        System.out.println(result);
    }

    private long check13(int[] elements, int pivot, boolean[] digits) {
        long result = 0L;
        for (int i = 0; i < 10; ++i) {
            if (!digits[i] && 0 == (pivot + i) % 13) {
                elements[8] = i;
                digits[i] = true;
                result += check17(elements, ((pivot + i) % 100) * 10, digits);
                digits[i] = false;
            }
        }
        return result;
    }

    private long check17(int[] elements, int pivot, boolean[] digits) {
        long result = 0L;
        for (int i = 0; i < 10; ++i) {
            if (!digits[i] && 0 == (pivot + i) % 17) {
                elements[9] = i;
                digits[i] = true;
                fill(elements, digits);
                result += permutation(elements, 0, 5);
                digits[i] = false;
            }
        }
        return result;
    }

    private void fill(int[] elements, boolean[] digits) {
        int index = 4;
        for (int i = digits.length - 1; i >= 0; --i) {
            if (!digits[i]) {
                elements[index] = i;
                --index;
            }
        }
    }

    private long permutation(int[] elements, int index, int length) {
        if (index == length) {
            if (0 == elements[0] || 0 != (elements[3] & 1) || 0 != (elements[2] + elements[3] + elements[4]) % 3 || 0 != (10 * elements[4] + elements[5] - (elements[6] << 1)) % 7) {
                return 0L;
            }

            long result = 0L;
            for (int element : elements) {
                result = result * 10 + element;
            }
            return result;
        }

        long result = permutation(elements, index + 1, length);
        for (int i = index + 1; i < length; ++i) {
            swap(elements, index, i);
            result += permutation(elements, index + 1, length);
            swap(elements, index, i);
        }
        return result;
    }

    private static void swap(int[] arrays, int i, int j) {
        arrays[i] ^= arrays[j];
        arrays[j] ^= arrays[i];
        arrays[i] ^= arrays[j];
    }
}

package project_euler;

public class Problem024 {
    public void solution() {
        long target = 1000000L;
        int[] elements = new int[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        permutation(target - 1, elements, elements.length, 0);

        long result = 0L;
        for (int element : elements) {
            result = result * 10 + element;
        }
        System.out.println(result);
    }

    private void permutation(long sequence, int[] elements, int length, int start) {
        if (1 == length - start) {
            return;
        }

        long count = getFactorial(length - start - 1);
        int index = (int) (sequence / count) + start;
        if (index != start) {
            int auxiliary = elements[index];
            System.arraycopy(elements, start, elements, start + 1, index - start);
            elements[start] = auxiliary;
        }
        ++start;
        permutation(sequence % count, elements, length, start);
    }

    private long getFactorial(int value) {
        long result = 1L;
        for (int i = 2; i <= value; ++i) {
            result *= i;
        }
        return result;
    }
}

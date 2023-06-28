package project_euler;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Problem093 {
    public void solution() {
        char[] signs = new char[]{'+', '-', '*', '/'};
        List<char[]> operations = new ArrayList<>();
        getOperations(signs, operations);

        int[] elements = new int[]{1, 2, 3, 4, 5, 6, 7, 8, 9};
        int[] auxiliary = new int[4];
        Arithmetic result = new Arithmetic(0, 0);
        Set<Integer> calculations = new HashSet<>();
        combination(elements, 0, 4, elements.length, auxiliary, 0, operations, result, calculations);
        System.out.println(result.value);
    }

    private void getOperations(char[] signs, List<char[]> operations) {
        char[] auxiliary = new char[3];
        search(signs, 3, operations, auxiliary, 0);
    }

    private void combination(int[] elements, int index, int count, int length, int[] auxiliary, int size, List<char[]> operations, Arithmetic pivot, Set<Integer> calculations) {
        if (count == size) {
            calculations.clear();
            permutation(auxiliary, 0, count, operations, calculations);
            int border = 1;
            while (calculations.contains(border)) {
                ++border;
            }
            --border;
            if (pivot.border < border) {
                pivot.border = border;
                pivot.value = 0;
                for (int value : auxiliary) {
                    pivot.value = pivot.value * 10 + value;
                }
            }
            return;
        }

        for (int i = index; i < length; ++i) {
            auxiliary[size] = elements[i];
            ++size;
            combination(elements, i + 1, count, length, auxiliary, size, operations, pivot, calculations);
            --size;
        }
    }

    private void search(char[] signs, int count, List<char[]> operations, char[] auxiliary, int size) {
        if (count == size) {
            operations.add(auxiliary.clone());
            return;
        }

        for (char value : signs) {
            auxiliary[size] = value;
            ++size;
            search(signs, count, operations, auxiliary, size);
            --size;
        }
    }

    private void permutation(int[] elements, int index, int length, List<char[]> operations, Set<Integer> calculations) {
        if (index == length) {
            for (char[] operation : operations) {
                addCalculations(calculate(operation[2], calculate(operation[1], calculate(operation[0], elements[0], elements[1]), elements[2]), elements[3]), calculations);
                addCalculations(calculate(operation[1], calculate(operation[0], elements[0], elements[1]), calculate(operation[2], elements[2], elements[3])), calculations);
                addCalculations(calculate(operation[2], calculate(operation[0], elements[0], calculate(operation[1], elements[1], elements[2])), elements[3]), calculations);
                addCalculations(calculate(operation[0], elements[0], calculate(operation[2], calculate(operation[1], elements[1], elements[2]), elements[3])), calculations);
                addCalculations(calculate(operation[0], elements[0], calculate(operation[1], elements[1], calculate(operation[2], elements[2], elements[3]))), calculations);
            }
            return;
        }

        permutation(elements, index + 1, length, operations, calculations);
        for (int i = index + 1; i < length; ++i) {
            swap(elements, index, i);
            permutation(elements, index + 1, length, operations, calculations);
            swap(elements, index, i);
        }
    }

    private void addCalculations(double value, Set<Integer> calculations) {
        if (value > 0 && Math.abs(Math.floor(value + 0.5) - value) < 0.00000001) {
            calculations.add((int) value);
        }
    }

    private double calculate(char sign, double i, double j) {
        if ('+' == sign) {
            return i + j;
        }
        if ('-' == sign) {
            return i - j;
        }
        if ('*' == sign) {
            return i * j;
        }
        if (Math.abs(j) < 0.00000001) {
            return -1.0;
        }
        return i / j;
    }

    private void swap(int[] arrays, int i, int j) {
        arrays[i] ^= arrays[j];
        arrays[j] ^= arrays[i];
        arrays[i] ^= arrays[j];
    }

    private static class Arithmetic {
        public int border;
        public int value;

        public Arithmetic(int border, int value) {
            this.border = border;
            this.value = value;
        }
    }
}

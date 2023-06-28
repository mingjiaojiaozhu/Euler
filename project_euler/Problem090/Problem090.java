package project_euler;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Problem090 {
    public void solution() {
        int[] elements = new int[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 6};
        List<int[]> ways = new ArrayList<>();
        int[] auxiliary = new int[6];
        combination(elements, 0, 6, elements.length, ways, auxiliary, 0);

        List<Integer> squares = new ArrayList<>();
        for (int i = 1; i < 10; ++i) {
            squares.add(reverse9To6(i * i));
        }

        int result = 0;
        Set<Integer> arrangements = new HashSet<>();
        for (int i = ways.size() - 1; i >= 0; --i) {
            for (int j = 0; j <= i; ++j) {
                if (checkDigits(ways, i, j, squares, arrangements)) {
                    ++result;
                }
            }
        }
        System.out.println(result);
    }

    private void combination(int[] elements, int start, int count, int length, List<int[]> ways, int[] auxiliary, int size) {
        if (count == size) {
            ways.add(auxiliary.clone());
            return;
        }

        for (int i = start; i < length; ++i) {
            auxiliary[size] = elements[i];
            ++size;
            combination(elements, i + 1, count, length, ways, auxiliary, size);
            --size;
        }
    }

    private int reverse9To6(int value) {
        if (9 == value / 10) {
            value -= 30;
        }
        if (9 == value % 10) {
            value -= 3;
        }
        return value;
    }

    private boolean checkDigits(List<int[]> ways, int start, int end, List<Integer> squares, Set<Integer> arrangements) {
        arrangements.clear();
        for (int pivot : ways.get(start)) {
            for (int value : ways.get(end)) {
                arrangements.add(pivot * 10 + value);
                arrangements.add(value * 10 + pivot);
            }
        }

        for (int value : squares) {
            if (!arrangements.contains(value)) {
                return false;
            }
        }
        return true;
    }
}

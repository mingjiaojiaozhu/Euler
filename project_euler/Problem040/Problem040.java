package project_euler;

import java.util.ArrayList;
import java.util.List;

public class Problem040 {
    public void solution() {
        int target = 1000000;
        List<Integer> borders = new ArrayList<>();
        int index = 0;
        while (true) {
            int value = ((int) Math.pow(10, index) * (9 * index - 1) + 1) / 9;
            borders.add(value);
            if (value > target) {
                break;
            }
            ++index;
        }

        int result = 1;
        while (0 != target) {
            result *= getChampernowne(target, borders);
            target /= 10;
        }
        System.out.println(result);
    }

    private int getChampernowne(int value, List<Integer> borders) {
        int index = getIndex(value, borders) - 1;
        value -= borders.get(index) + 1;
        int digit = (int) Math.pow(10, index) + value / (index + 1);
        for (int i = value % (index + 1); i < index; ++i) {
            digit /= 10;
        }
        return digit % 10;
    }

    private int getIndex(int value, List<Integer> borders) {
        int start = 0;
        int end = borders.size() - 1;
        while (start <= end) {
            int current = start + ((end - start) >> 1);
            if (borders.get(current) <= value) {
                start = current + 1;
            } else {
                end = current - 1;
            }
        }
        return start;
    }
}

package project_euler;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Problem078 {
    public void solution() {
        int target = 1000000;
        List<Decimal> ways = new ArrayList<>();
        ways.add(setValue(1));
        ways.add(setValue(1));

        int length = 0;
        while (target >= (int) 1e5) {
            ++length;
            target /= (int) 1e5;
        }

        int result = 2;
        while (true) {
            Decimal way = getWay(result, ways);
            if (isDivideExactly(way, length, target)) {
                System.out.println(result);
                return;
            }
            ++result;
        }
    }

    private Decimal setValue(int value) {
        Decimal decimal = new Decimal(100, 0);
        decimal.value[0] = value;
        decimal.length = 1;
        return decimal;
    }

    private Decimal getWay(int target, List<Decimal> ways) {
        Decimal result = setValue(0);
        int factor = 1;
        for (int i = 1; i <= target; ++i) {
            if (!addDecimal(target - (i * (i * 3 - 1) >> 1), ways, factor, result) || !addDecimal(target - (i * (i * 3 + 1) >> 1), ways, factor, result)) {
                break;
            }
            factor *= -1;
        }
        ways.add(result);
        return result;
    }

    private boolean isDivideExactly(Decimal way, int length, int target) {
        if (way.length <= length) {
            return false;
        }

        for (int i = 0; i < length; ++i) {
            if (0 != way.value[i]) {
                return false;
            }
        }
        return 0 == way.value[length] % target;
    }

    private boolean addDecimal(int index, List<Decimal> ways, int factor, Decimal result) {
        if (index < 0) {
            return false;
        }
        getSummation(ways.get(index), factor, result);
        return true;
    }

    private void getSummation(Decimal decimal, int factor, Decimal summation) {
        for (int i = 0; i < decimal.length; ++i) {
            summation.value[i] += decimal.value[i] * factor;
        }

        if (factor > 0) {
            for (int i = 0; i < summation.length; ++i) {
                if (summation.value[i] >= (int) 1e5) {
                    summation.value[i + 1] += summation.value[i] / (int) 1e5;
                    summation.value[i] %= (int) 1e5;
                }
            }
            if (0 != summation.value[summation.length]) {
                ++summation.length;
            }
        } else {
            for (int i = 0; i < summation.length; ++i) {
                if (summation.value[i] < 0) {
                    --summation.value[i + 1];
                    summation.value[i] += (int) 1e5;
                }
            }
            while (0 == summation.value[summation.length - 1]) {
                --summation.length;
            }
        }
    }

    private static class Decimal {
        public int[] value;
        public int length;

        public Decimal(int capacity, int length) {
            this.value = new int[capacity];
            Arrays.fill(this.value, 0);
            this.length = length;
        }
    }
}

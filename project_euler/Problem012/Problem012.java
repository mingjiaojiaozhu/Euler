package project_euler;

public class Problem012 {
    public void solution() {
        int target = 500;
        int previous = getDivisors(1);
        int index = 1;
        while (true) {
            int current = getDivisors(index + 1);
            int value = previous * current;
            if (value > target) {
                break;
            }

            ++index;
            previous = current;
        }
        int result = index * (index + 1) >> 1;
        System.out.println(result);
    }

    private int getDivisors(int value) {
        int result = 1;
        if (0 == (value & 1)) {
            int power = 0;
            while (0 == (value & 1)) {
                value >>= 1;
                ++power;
            }
            result *= power;
        }

        int factor = 3;
        while (factor <= value) {
            int power = 0;
            while (0 == value % factor) {
                value /= factor;
                ++power;
            }
            result *= power + 1;
            factor += 2;
        }
        return result;
    }
}

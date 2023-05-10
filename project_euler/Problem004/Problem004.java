package project_euler;

public class Problem004 {
    public void solution() {
        int target = 100;
        int result = 0;
        for (int i = 999; i >= target; --i) {
            for (int j = i; j >= target; --j) {
                int value = i * j;
                if (isPalindrome(value) && result < value) {
                    result = value;
                    target = j;
                    break;
                }
            }
        }
        System.out.println(result);
    }

    private boolean isPalindrome(int value) {
        int divisor = 1;
        while (10 <= value / divisor) {
            divisor *= 10;
        }

        while (value > 1) {
            int head = value / divisor;
            int tail = value % 10;
            if (head != tail) {
                return false;
            }

            value = value % divisor / 10;
            divisor /= 100;
        }
        return true;
    }
}

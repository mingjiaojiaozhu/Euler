package project_euler;

public class Problem007 {
    public void solution() {
        int target = 10001;
        int result = 1;
        int count = 1;
        while (count < target) {
            result += 2;
            if (isPrime(result)) {
                ++count;
            }
        }
        System.out.println(result);
    }

    private boolean isPrime(int value) {
        if (1 != value % 6 && 5 != value % 6) {
            return 2 == value || 3 == value;
        }

        int border = (int) Math.sqrt(value);
        for (int i = 5; i <= border; i += 6) {
            if (0 == value % i || 0 == value % (i + 2)) {
                return false;
            }
        }
        return 1 != value;
    }
}

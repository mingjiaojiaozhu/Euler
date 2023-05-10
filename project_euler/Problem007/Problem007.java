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
        if (0 == (value & 1)) {
            return 2 == value;
        }

        int border = (int) Math.sqrt(value);
        for (int i = 3; i <= border; i += 2) {
            if (0 == value % i) {
                return false;
            }
        }
        return 1 != value;
    }
}

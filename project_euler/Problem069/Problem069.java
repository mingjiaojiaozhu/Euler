package project_euler;

public class Problem069 {
    public void solution() {
        int target = 1000000;
        int index = 3;
        int result = 2;
        while (true) {
            if (isPrime(index)) {
                if (result * index >= target) {
                    System.out.println(result);
                    return;
                }
                result *= index;
            }
            index += 2;
        }
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

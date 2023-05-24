package project_euler;

public class Problem027 {
    public void solution() {
        int target = 1000;
        int border = -1 * (target - 1);
        int result = 0;
        int pivot = 0;
        for (int i = 3; i < target; i += 2) {
            if (!isPrime(i)) {
                continue;
            }

            for (int j = border; j < target; j += 2) {
                int count = 1;
                while (isPrime(count * count + count * j + i)) {
                    ++count;
                }
                if (pivot < count) {
                    pivot = count;
                    result = i * j;
                }
            }
        }
        System.out.println(result);
    }

    private boolean isPrime(int value) {
        if (value <= 0) {
            return false;
        }
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

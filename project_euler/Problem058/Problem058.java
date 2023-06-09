package project_euler;

public class Problem058 {
    public void solution() {
        double target = 0.1;
        int index = 3;
        int count = 0;
        while (true) {
            int value = index * index;
            for (int i = 0; i < 3; ++i) {
                value -= index - 1;
                if (isPrime(value)) {
                    ++count;
                }
            }

            if ((double) count < ((index << 1) - 1) * target) {
                System.out.println(index);
                return;
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

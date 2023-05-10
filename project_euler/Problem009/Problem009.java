package project_euler;

public class Problem009 {
    public void solution() {
        int target = 1000;
        for (int i = target / 3; i > 0; --i) {
            for (int j = target >> 1; j > i; --j) {
                int remainder = target - i - j;
                if (i * i + j * j == remainder * remainder) {
                    System.out.println(i * j * remainder);
                    return;
                }
            }
        }
    }
}

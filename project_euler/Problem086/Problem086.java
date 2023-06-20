package project_euler;

public class Problem086 {
    public void solution() {
        int target = 1000000;
        int count = 0;
        int result = 1;
        while (count < target) {
            ++result;
            for (int i = 3; i < result; ++i) {
                double root = Math.sqrt(result * result + i * i);
                if (Math.abs(Math.floor(root + 0.5) - root) < 0.00000001) {
                    count += i >> 1;
                }
            }
            for (int i = (result << 1) - 1; i >= result; --i) {
                double root = Math.sqrt(result * result + i * i);
                if (Math.abs(Math.floor(root + 0.5) - root) < 0.00000001) {
                    count += result - ((i + 1) >> 1) + 1;
                }
            }
        }
        System.out.println(result);
    }
}

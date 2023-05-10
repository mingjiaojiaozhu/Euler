package project_euler;

public class Problem015 {
    public void solution() {
        int target = 20;
        int border = target << 1;
        long result = 1L;
        for (int i = border - 1; i > target; i -= 2) {
            result = (result << 1) * i / ((border - i + 1) >> 1);
        }
        System.out.println(result);
    }
}

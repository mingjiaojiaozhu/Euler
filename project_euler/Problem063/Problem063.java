package project_euler;

public class Problem063 {
    public void solution() {
        int result = 0;
        for (int i = 1; i < 10; ++i) {
            result += (int) (1.0 / (1 - Math.log10(i)));
        }
        System.out.println(result);
    }
}

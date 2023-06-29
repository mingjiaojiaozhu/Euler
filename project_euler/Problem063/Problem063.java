package project_euler;

public class Problem063 {
    public void solution() {
        int result = 0;
        for (int i = 1; i < 10; ++i) {
            result += (int) ((double) 1 / (1 - Math.log10(i)));
        }
        System.out.println(result);
    }
}

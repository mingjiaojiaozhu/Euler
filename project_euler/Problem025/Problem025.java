package project_euler;

public class Problem025 {
    public void solution() {
        int target = 1000;
        int result = (int) Math.ceil(((double) target - 1 + Math.log10(5) / 2) / Math.log10((1 + Math.sqrt(5)) / 2));
        System.out.println(result);
    }
}

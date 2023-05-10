package project_euler;

public class Problem006 {
    public void solution() {
        int target = 100;
        int result = target * (target - 1) * (target + 1) * (3 * target + 2) / 12;
        System.out.println(result);
    }
}

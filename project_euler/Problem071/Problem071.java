package project_euler;

public class Problem071 {
    public void solution() {
        int target = 1000000;
        int index = (target - 5) / 7;
        int result = index * 3 + 2;
        System.out.println(result);
    }
}

package project_euler;

public class Problem001 {
    public void solution() {
        int target = 1000;
        int result = getSummation(target, 3) + getSummation(target, 5) - getSummation(target, 3 * 5);
        System.out.println(result);
    }

    private int getSummation(int border, int factor) {
        int count = (border - 1) / factor;
        return factor * count * (count + 1) >> 1;
    }
}

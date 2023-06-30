package project_euler;

public class Problem100 {
    public void solution() {
        long target = 1000000000000L;
        long index = 1L;
        long result = 1L;
        while (index < target) {
            long auxiliary = (index << 1) + result * 3 - 2;
            index = index * 3 + (result << 2) - 3;
            result = auxiliary;
        }
        System.out.println(result);
    }
}

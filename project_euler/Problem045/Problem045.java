package project_euler;

public class Problem045 {
    public void solution() {
        long index = 144L;
        while (true) {
            long hexagon = index * ((index << 1) - 1);
            if (isPentagon(hexagon)) {
                System.out.println(hexagon);
                return;
            }
            ++index;
        }
    }

    private boolean isPentagon(long value) {
        double auxiliary = Math.sqrt(value * 24 + 1);
        return Math.abs(Math.floor(auxiliary + 0.5) - auxiliary) < 0.00000001 && 0 == ((long) auxiliary + 1) % 6;
    }
}

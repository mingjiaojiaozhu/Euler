package project_euler;

public class Problem045 {
    public void solution() {
        long index = 144;
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
        long delta = value * 24 + 1;
        return Math.abs(Math.floor(Math.sqrt(delta) + 0.5) - Math.sqrt(delta)) < 0.00000001 && 0 == ((long) Math.sqrt(delta) + 1) % 6;
    }
}

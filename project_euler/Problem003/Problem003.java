package project_euler;

public class Problem003 {
    public void solution() {
        long target = 600851475143L;
        while (0 == (target & 1L)) {
            target >>= 1;
        }
        if (1L == target) {
            target = 2L;
        }

        long factor = 3L;
        while (factor < target) {
            while (0L == target % factor && target != factor) {
                target /= factor;
            }
            factor += 2L;
        }
        System.out.println(target);
    }
}

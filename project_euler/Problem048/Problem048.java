package project_euler;

public class Problem048 {
    public void solution() {
        int target = 1000;
        int[] product = new int[2];
        long[] auxiliary = new long[2];
        long result = 0L;
        for (int i = target / 10 * 10 + 1; i <= target; ++i) {
            getPower(i, i, product, auxiliary);
            result += (long) product[1] * (long) 1e5 + product[0];
        }
        for (int i = target / 10 - 1; i >= 0; --i) {
            for (int j = 1; j < 10; ++j) {
                int value = i * 10 + j;
                getPower(value, value, product, auxiliary);
                result += (long) product[1] * (long) 1e5 + product[0];
            }
        }
        System.out.println(result % (long) 1e10);
    }

    private void getPower(int base, int index, int[] product, long[] auxiliary) {
        if (1 == index) {
            product[0] = base;
            product[1] = 0;
            return;
        }

        getPower(base, index >> 1, product, auxiliary);
        getSquare(product, auxiliary);
        if (0 != (index & 1)) {
            getProduct(base, product);
        }
    }

    private void getSquare(int[] product, long[] auxiliary) {
        auxiliary[0] = (long) product[0] * product[0];
        auxiliary[1] = (long) product[0] * product[1] << 1;
        if (auxiliary[0] >= (long) 1e5) {
            auxiliary[1] += auxiliary[0] / (long) 1e5;
            auxiliary[0] %= (long) 1e5;
        }
        auxiliary[1] %= (long) 1e5;
        for (int i = 0; i < 2; ++i) {
            product[i] = (int) auxiliary[i];
        }
    }

    private void getProduct(int value, int[] product) {
        product[0] *= value;
        product[1] *= value;
        if (product[0] >= (int) 1e5) {
            product[1] += product[0] / (int) 1e5;
            product[0] %= (int) 1e5;
        }
        product[1] %= (int) 1e5;
    }
}

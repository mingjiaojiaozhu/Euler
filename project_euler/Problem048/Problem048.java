package project_euler;

public class Problem048 {
    public void solution() {
        int target = 1000;
        long[] product = new long[2];
        long[] auxiliary = new long[2];
        long result = 0L;
        for (int i = target / 10 * 10 + 1; i <= target; ++i) {
            getPower(i, i, product, auxiliary);
            result += product[1] * (long) 1e5 + product[0];
        }
        for (int i = target / 10 - 1; i >= 0; --i) {
            for (int j = 1; j < 10; ++j) {
                int value = i * 10 + j;
                getPower(value, value, product, auxiliary);
                result += product[1] * (long) 1e5 + product[0];
            }
        }
        System.out.println(result % (long) 1e10);
    }

    private void getPower(int base, int index, long[] product, long[] auxiliary) {
        if (1 == index) {
            product[0] = base;
            product[1] = 0L;
            return;
        }

        getPower(base, index >> 1, product, auxiliary);
        getSquare(product, auxiliary);
        if (0 != (index & 1)) {
            getProduct(base, product);
        }
    }

    private void getSquare(long[] product, long[] auxiliary) {
        auxiliary[0] = product[0] * product[0];
        auxiliary[1] = product[0] * product[1] + product[1] * product[0];
        if (auxiliary[0] >= (long) 1e5) {
            auxiliary[1] += auxiliary[0] / (long) 1e5;
            auxiliary[0] %= (long) 1e5;
        }
        auxiliary[1] %= (long) 1e5;
        System.arraycopy(auxiliary, 0, product, 0, 2);
    }

    private void getProduct(int value, long[] product) {
        product[0] *= value;
        product[1] *= value;
        if (product[0] >= (long) 1e5) {
            product[1] += product[0] / (long) 1e5;
            product[0] %= (long) 1e5;
        }
        product[1] %= (long) 1e5;
    }
}

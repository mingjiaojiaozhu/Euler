package project_euler;

public class Problem097 {
    public void solution() {
        int target = 7830457;
        int factor = 28433;
        int[] product = new int[2];
        long[] auxiliary = new long[2];
        getPower(target, product, auxiliary);
        getProduct(factor, 1, product, auxiliary);

        long result = (long) product[1] * (long) 1e5 + product[0];
        System.out.println(result);
    }

    private void getPower(int value, int[] product, long[] auxiliary) {
        if (value < 8) {
            product[0] = (int) Math.pow(2, value);
            product[1] = 0;
            return;
        }

        getPower(value >> 1, product, auxiliary);
        getSquare(product, auxiliary);
        if (0 != (value & 1)) {
            getDouble(product);
        }
    }

    private void getProduct(int factor, int value, int[] product, long[] auxiliary) {
        auxiliary[0] = (long) product[0] * factor + value;
        auxiliary[1] = (long) product[1] * factor;
        carry(product, auxiliary);
    }

    private void getSquare(int[] product, long[] auxiliary) {
        auxiliary[0] = (long) product[0] * product[0];
        auxiliary[1] = (long) product[0] * product[1] << 1;
        carry(product, auxiliary);
    }

    private void getDouble(int[] product) {
        product[0] <<= 1;
        product[1] <<= 1;
        if (product[0] >= (int) 1e5) {
            product[1] += product[0] / (int) 1e5;
            product[0] %= (int) 1e5;
        }
        product[1] %= (int) 1e5;
    }

    private void carry(int[] product, long[] auxiliary) {
        if (auxiliary[0] >= (long) 1e5) {
            auxiliary[1] += auxiliary[0] / (long) 1e5;
            auxiliary[0] %= (long) 1e5;
        }
        auxiliary[1] %= (long) 1e5;
        for (int i = 0; i < 2; ++i) {
            product[i] = (int) auxiliary[i];
        }
    }
}

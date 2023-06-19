#include <iostream>
#include <vector>
using namespace std;

class Problem048 {
public:
    void solution() {
        int target = 1000;
        vector<int> product(2);
        vector<long long> auxiliary(2);
        long long result = 0L;
        for (int i = target / 10 * 10 + 1; i <= target; ++i) {
            get_power(i, i, product, auxiliary);
            result += (long long) product[1] * (long long) 1e5 + product[0];
        }
        for (int i = target / 10 - 1; i >= 0; --i) {
            for (int j = 1; j < 10; ++j) {
                int value = i * 10 + j;
                get_power(value, value, product, auxiliary);
                result += (long long) product[1] * (long long) 1e5 + product[0];
            }
        }
        cout << result % (long long) 1e10 << endl;
    }

private:
    void get_power(int base, int index, vector<int> &product, vector<long long> &auxiliary) {
        if (1 == index) {
            product[0] = base;
            product[1] = 0;
            return;
        }

        get_power(base, index >> 1, product, auxiliary);
        get_square(product, auxiliary);
        if (index & 1) {
            get_product(base, product);
        }
    }

    static void get_square(vector<int> &product, vector<long long> &auxiliary) {
        auxiliary[0] = (long long) product[0] * product[0];
        auxiliary[1] = (long long) product[0] * product[1] << 1;
        if (auxiliary[0] >= (long long) 1e5) {
            auxiliary[1] += auxiliary[0] / (long long) 1e5;
            auxiliary[0] %= (long long) 1e5;
        }
        auxiliary[1] %= (long long) 1e5;
        for (int i = 0; i < 2; ++i) {
            product[i] = (int) auxiliary[i];
        }
    }

    static void get_product(int value, vector<int> &product) {
        product[0] *= value;
        product[1] *= value;
        if (product[0] >= (int) 1e5) {
            product[1] += product[0] / (int) 1e5;
            product[0] %= (int) 1e5;
        }
        product[1] %= (int) 1e5;
    }
};

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Problem097 {
public:
    void solution() {
        int target = 7830457;
        int factor = 28433;
        vector<int> product(2);
        vector<long long> auxiliary(2);
        get_power(target, product, auxiliary);
        get_product(factor, 1, product, auxiliary);

        long long result = (long long) product[1] * (long long) 1e5 + product[0];
        cout << result << endl;
    }

private:
    void get_power(int value, vector<int> &product, vector<long long> &auxiliary) {
        if (value < 8) {
            product[0] = (int) pow(2, value);
            product[1] = 0;
            return;
        }

        get_power(value >> 1, product, auxiliary);
        get_square(product, auxiliary);
        if (value & 1) {
            get_double(product);
        }
    }

    void get_product(int factor, int value, vector<int> &product, vector<long long> &auxiliary) {
        auxiliary[0] = (long long) product[0] * factor + value;
        auxiliary[1] = (long long) product[1] * factor;
        carry(product, auxiliary);
    }

    void get_square(vector<int> &product, vector<long long> &auxiliary) {
        auxiliary[0] = (long long) product[0] * product[0];
        auxiliary[1] = (long long) product[0] * product[1] << 1;
        carry(product, auxiliary);
    }

    void get_double(vector<int> &product) {
        product[0] <<= 1;
        product[1] <<= 1;
        if (product[0] >= (int) 1e5) {
            product[1] += product[0] / (int) 1e5;
            product[0] %= (int) 1e5;
        }
        product[1] %= (int) 1e5;
    }

    void carry(vector<int> &product, vector<long long> &auxiliary) {
        if (auxiliary[0] >= (long long) 1e5) {
            auxiliary[1] += auxiliary[0] / (long long) 1e5;
            auxiliary[0] %= (long long) 1e5;
        }
        auxiliary[1] %= (long long) 1e5;
        for (int i = 0; i < 2; ++i) {
            product[i] = (int) auxiliary[i];
        }
    }
};

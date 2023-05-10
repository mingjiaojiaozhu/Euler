#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Problem016 {
public:
    void solution() {
        int target = 1000;
        int length = (target + 4) / 5;
        Decimal *decimal = new Decimal(length, 0);
        vector<int> auxiliary(length);
        get_power(target, decimal, auxiliary, length);

        int result = 0;
        for (int i = 0; i < decimal->length; ++i) {
            int value = decimal->value[i];
            while (value > 0) {
                result += value % 10;
                value /= 10;
            }
        }
        cout << result << endl;
    }

private:
    struct Decimal {
        vector<int> value;
        int length;

        Decimal(int capacity, int length): value(vector<int>(capacity, 0)), length(length) {}
    };

    void get_power(int value, Decimal *decimal, vector<int> &auxiliary, int length) {
        if (value < 8) {
            decimal->value[0] = (int) pow(2, value);
            decimal->length = 1;
            return;
        }

        get_power(value >> 1, decimal, auxiliary, length);
        get_square(decimal, auxiliary, length);
        if (value & 1) {
            get_double(decimal);
        }
    }

    static void get_square(Decimal *decimal, vector<int> &auxiliary, int length) {
        auxiliary.assign(length, 0);
        for (int i = 0; i < decimal->length; ++i) {
            for (int j = 0; j < decimal->length; ++j) {
                long long result = (long long) decimal->value[i] * decimal->value[j];
                int index = i + j;
                auxiliary[index] += (int) (result % (int) 1e5);
                auxiliary[index + 1] += (int) (result / (int) 1e5);
            }
        }

        decimal->length = (decimal->length << 1) - 1;
        for (int i = 0; i < decimal->length; ++i) {
            if (auxiliary[i] >= (int) 1e5) {
                auxiliary[i + 1] += auxiliary[i] / (int) 1e5;
                auxiliary[i] %= (int) 1e5;
            }
        }
        if (auxiliary[decimal->length]) {
            ++decimal->length;
        }
        decimal->value.assign(auxiliary.begin(), auxiliary.begin() + decimal->length);
    }

    static void get_double(Decimal *decimal) {
        for (int i = 0; i < decimal->length; ++i) {
            decimal->value[i] <<= 1;
        }

        for (int i = 0; i < decimal->length; ++i) {
            if (decimal->value[i] >= (int) 1e5) {
                decimal->value[i + 1] += decimal->value[i] / (int) 1e5;
                decimal->value[i] %= (int) 1e5;
            }
        }
        if (decimal->value[decimal->length]) {
            ++decimal->length;
        }
    }
};

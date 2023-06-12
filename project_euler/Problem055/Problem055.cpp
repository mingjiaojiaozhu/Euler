#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Problem055 {
public:
    void solution() {
        int target = 10000;
        Decimal *decimal = new Decimal(100, 0);
        vector<int> auxiliary(100);
        int result = 0;
        for (int i = 1; i < target; ++i) {
            if (is_lychrel(i, decimal, auxiliary)) {
                ++result;
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

    bool is_lychrel(int value, Decimal *decimal, vector<int> &auxiliary) {
        set_value(value, decimal);
        reverse_value(decimal, auxiliary);
        get_summation(decimal, auxiliary);

        int count = 0;
        while (count < 50) {
            reverse_value(decimal, auxiliary);
            if (is_equal(decimal, auxiliary)) {
                return false;
            }
            get_summation(decimal, auxiliary);
            ++count;
        }
        return true;
    }

    void set_value(int value, Decimal *decimal) {
        decimal->value.assign(100, 0);
        decimal->length = 0;
        while (value) {
            decimal->value[decimal->length] = value % (int) 1e5;
            ++decimal->length;
            value /= (int) 1e5;
        }
    }

    void reverse_value(Decimal *decimal, vector<int> &auxiliary) {
        auxiliary.assign(100, 0);
        int index = 0;
        int count = 0;
        for (int i = decimal->length - 1; i >= 0; --i) {
            int value = decimal->value[i];
            int divisor = (int) 1e5 / 10;
            if (i == decimal->length - 1) {
                while (!(value / divisor)) {
                    divisor /= 10;
                }
            }
            while (divisor) {
                auxiliary[index] += (value / divisor) * (int) pow(10, count);
                value %= divisor;
                divisor /= 10;
                ++count;
                if (5 == count) {
                    ++index;
                    count = 0;
                }
            }
        }
    }

    void get_summation(Decimal *decimal, vector<int> &auxiliary) {
        for (int i = 0; i < decimal->length; ++i) {
            decimal->value[i] += auxiliary[i];
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

    int is_equal(Decimal *decimal, vector<int> &auxiliary) {
        for (int i = 0; i < decimal->length; ++i) {
            if (decimal->value[i] != auxiliary[i]) {
                return false;
            }
        }
        return true;
    }
};

#include <iostream>
#include <vector>
using namespace std;

class Problem056 {
public:
    void solution() {
        int target = 100;
        Decimal *decimal = new Decimal(target, 0);
        int result = 0;
        for (int i = 2; i < target; ++i) {
            decimal->value.assign(target, 0);
            set_value(i, decimal);
            for (int j = 2; j < target; ++j) {
                get_product(i, decimal);
                result = get_digital(decimal, result);
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

    void set_value(int value, Decimal *decimal) {
        decimal->value[0] = value;
        decimal->length = 1;
    }

    void get_product(int value, Decimal *decimal) {
        for (int i = 0; i < decimal->length; ++i) {
            decimal->value[i] *= value;
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

    int get_digital(Decimal *decimal, int pivot) {
        int result = 0;
        for (int i = 0; i < decimal->length; ++i) {
            int value = decimal->value[i];
            while (value) {
                result += value % 10;
                value /= 10;
            }
        }
        return max(result, pivot);
    }
};

#include <iostream>
#include <vector>
using namespace std;

class Problem020 {
public:
    void solution() {
        int target = 100;
        Decimal *decimal = new Decimal(target, 0);
        decimal->value[0] = target;
        decimal->length = 1;

        for (int i = target - 1; i > 1; --i) {
            get_product(i, decimal);
        }

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
};

#include <iostream>
#include <vector>
using namespace std;

class Problem065 {
public:
    void solution() {
        int target = 100;
        Decimal *previous = new Decimal(100, 0);
        Decimal *current = new Decimal(100, 0);
        set_value(1, previous);
        set_value(2, current);
        for (int i = 2; i <= target; ++i) {
            int factor = 1;
            if (!(i % 3)) {
                factor = (i << 1) / 3;
            }
            get_summation(current, factor, previous);
            swap_decimal(previous, current);
        }

        int result = 0;
        for (int i = 0; i < current->length; ++i) {
            int value = current->value[i];
            while (value) {
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

    void set_value(int value, Decimal *decimal) {
        decimal->value[0] = value;
        decimal->length = 1;
    }

    void get_summation(Decimal *decimal, int factor, Decimal *summation) {
        for (int i = 0; i < decimal->length; ++i) {
            summation->value[i] += decimal->value[i] * factor;
        }

        for (int i = 0; i < summation->length; ++i) {
            if (summation->value[i] >= (int) 1e5) {
                summation->value[i + 1] += summation->value[i] / (int) 1e5;
                summation->value[i] %= (int) 1e5;
            }
        }
        if (summation->value[summation->length]) {
            ++summation->length;
        }
    }

    void swap_decimal(Decimal *previous, Decimal *current) {
        int length = max(previous->length, current->length);
        for (int i = 0; i < length; ++i) {
            previous->value[i] ^= current->value[i];
            current->value[i] ^= previous->value[i];
            previous->value[i] ^= current->value[i];
        }
        previous->length ^= current->length;
        current->length ^= previous->length;
        previous->length ^= current->length;
    }
};

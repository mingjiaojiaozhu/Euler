#include <iostream>
#include <vector>
using namespace std;

class Problem057 {
public:
    void solution() {
        int target = 1000;
        Decimal *numerator = new Decimal(100, 0);
        Decimal *denominator = new Decimal(100, 0);
        set_value(3, numerator);
        set_value(2, denominator);

        int result = 0;
        for (int i = 2; i < target; ++i) {
            get_summation(denominator, numerator);
            get_summation(numerator, denominator);
            swap_decimal(numerator, denominator);
            if (numerator->length > denominator->length || get_digits(numerator->value[numerator->length - 1]) > get_digits(denominator->value[denominator->length - 1])) {
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

    void set_value(int value, Decimal *decimal) {
        decimal->value[0] = value;
        decimal->length = 1;
    }

    void get_summation(Decimal *decimal, Decimal *summation) {
        for (int i = 0; i < decimal->length; ++i) {
            summation->value[i] += decimal->value[i];
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

    void swap_decimal(Decimal *numerator, Decimal *denominator) {
        int length = max(numerator->length, denominator->length);
        for (int i = 0; i < length; ++i) {
            numerator->value[i] ^= denominator->value[i];
            denominator->value[i] ^= numerator->value[i];
            numerator->value[i] ^= denominator->value[i];
        }
        numerator->length ^= denominator->length;
        denominator->length ^= numerator->length;
        numerator->length ^= denominator->length;
    }

    int get_digits(int value) {
        int result = 0;
        while (value) {
            ++result;
            value /= 10;
        }
        return result;
    }
};

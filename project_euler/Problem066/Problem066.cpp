#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Problem066 {
public:
    void solution() {
        int target = 1000;
        vector<int> factors(0);
        Decimal *previous = new Decimal(100, 0);
        Decimal *current = new Decimal(100, 0);
        Decimal *auxiliary = new Decimal(100, 0);

        int result = 0;
        Decimal *pivot = new Decimal(100, 0);
        for (int i = 5; i <= target; ++i) {
            if (get_solution(i, factors, previous, current, auxiliary) && is_greater(current, pivot)) {
                swap_decimal(current, pivot);
                result = i;
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

    bool get_solution(int value, vector<int> &factors, Decimal *previous, Decimal *current, Decimal *auxiliary) {
        factors.clear();
        int start = get_period(value, factors);
        if (!start) {
            return false;
        }

        set_value(0, previous);
        set_value(1, current);
        get_convergents(previous, current, factors);
        if ((int) factors.size() & 1) {
            return true;
        }

        set_value(1, previous);
        set_value(start, auxiliary);
        get_convergents(previous, auxiliary, factors);
        swap_decimal(previous, current);
        get_product(previous, auxiliary, current);
        get_double(current);
        return true;
    }

    bool is_greater(Decimal *current, Decimal *pivot) {
        if (current->length != pivot->length) {
            return current->length > pivot->length;
        }

        for (int i = current->length - 1; i >= 0; --i) {
            if (current->value[i] != pivot->value[i]) {
                return current->value[i] > pivot->value[i];
            }
        }
        return false;
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

    int get_period(int value, vector<int> &factors) {
        if (fabs(floor(sqrt(value) + 0.5) - sqrt(value)) < 0.00000001) {
            return 0;
        }

        int initial = (int) sqrt(value);
        int pivot = initial << 1;
        int current = initial;
        int offset = 0;
        int factor = 1;
        while (current != pivot) {
            offset = current * factor - offset;
            factor = (value - offset * offset) / factor;
            current = (initial + offset) / factor;
            factors.emplace_back(current);
        }
        factors.pop_back();
        return initial;
    }

    void set_value(int value, Decimal *decimal) {
        decimal->value.assign(100, 0);
        decimal->value[0] = value;
        decimal->length = 1;
    }

    void get_convergents(Decimal *previous, Decimal *current, const vector<int> &factors) {
        for (int factor : factors) {
            get_summation(current, factor, previous);
            swap_decimal(previous, current);
        }
    }

    void get_product(Decimal *multiplicand, Decimal *multiplier, Decimal *product) {
        for (int i = 0; i < multiplicand->length; ++i) {
            for (int j = 0; j < multiplier->length; ++j) {
                long long value = (long long) multiplicand->value[i] * multiplier->value[j];
                int index = i + j;
                product->value[index] += (int) (value % (int) 1e5);
                product->value[index + 1] += (int) (value / (int) 1e5);
            }
        }
        product->length = multiplicand->length + multiplier->length - 1;
        carry(product);
    }

    void get_double(Decimal *decimal) {
        for (int i = 0; i < decimal->length; ++i) {
            decimal->value[i] <<= 1;
        }
        carry(decimal);
    }

    void get_summation(Decimal *decimal, int factor, Decimal *summation) {
        for (int i = 0; i < decimal->length; ++i) {
            summation->value[i] += decimal->value[i] * factor;
        }
        carry(summation);
    }

    void carry(Decimal *decimal) {
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

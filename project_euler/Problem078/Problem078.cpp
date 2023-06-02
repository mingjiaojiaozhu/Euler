#include <iostream>
#include <vector>
using namespace std;

class Problem078 {
public:
    void solution() {
        int target = 1000000;
        vector<Decimal *> ways(0);
        ways.emplace_back(set_value(1, 1));
        ways.emplace_back(set_value(1, 1));

        int length = 0;
        while (target >= (int) 1e5) {
            ++length;
            target /= (int) 1e5;
        }

        Decimal *current = new Decimal(100, 0);
        int result = 2;
        while (true) {
            Decimal *way = get_way(result, ways, current);
            if (is_divide_exactly(way, length, target)) {
                cout << result << endl;
                return;
            }
            ++result;
        }
    }

private:
    struct Decimal {
        vector<int> value;
        int length;

        Decimal(int capacity, int length): value(vector<int>(capacity, 0)), length(length) {}
    };

    Decimal *set_value(int value, int length) {
        Decimal *decimal = new Decimal(length, 0);
        decimal->value[0] = value;
        decimal->length = 1;
        return decimal;
    }

    Decimal *get_way(int target, vector<Decimal *> &ways, Decimal *current) {
        int factor = 1;
        for (int i = 1; i <= target; ++i) {
            if (!add_decimal(target - (i * (i * 3 - 1) >> 1), ways, factor, current) || !add_decimal(target - (i * (i * 3 + 1) >> 1), ways, factor, current)) {
                break;
            }
            factor *= -1;
        }
        Decimal *result = new Decimal(current->length, 0);
        swap_decimal(current, result);
        ways.emplace_back(result);
        return result;
    }

    bool is_divide_exactly(Decimal *way, int length, int target) {
        if (way->length <= length) {
            return false;
        }

        for (int i = 0; i < length; ++i) {
            if (way->value[i]) {
                return false;
            }
        }
        return !(way->value[length] % target);
    }

    bool add_decimal(int index, vector<Decimal *> &ways, int factor, Decimal *summation) {
        if (index < 0) {
            return false;
        }
        get_summation(ways[index], factor, summation);
        return true;
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

    void get_summation(Decimal *decimal, int factor, Decimal *summation) {
        for (int i = 0; i < decimal->length; ++i) {
            summation->value[i] += decimal->value[i] * factor;
        }

        if (factor > 0) {
            for (int i = 0; i < summation->length; ++i) {
                if (summation->value[i] >= (int) 1e5) {
                    summation->value[i + 1] += summation->value[i] / (int) 1e5;
                    summation->value[i] %= (int) 1e5;
                }
            }
            if (summation->value[summation->length]) {
                ++summation->length;
            }
        } else {
            for (int i = 0; i < summation->length; ++i) {
                if (summation->value[i] < 0) {
                    --summation->value[i + 1];
                    summation->value[i] += (int) 1e5;
                }
            }
            while (!summation->value[summation->length - 1]) {
                --summation->length;
            }
        }
    }
};

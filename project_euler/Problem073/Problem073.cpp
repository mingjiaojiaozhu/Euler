#include <iostream>
#include <unordered_map>
using namespace std;

class Problem073 {
public:
    void solution() {
        int target = 12000;
        unordered_map<int, int> fractions(0);
        fractions.insert(pair<int, int>(1, get_count(1)));
        int result = get_fractions(target, fractions) - fractions[1];
        cout << result << endl;
    }

private:
    int get_fractions(int target, unordered_map<int, int> &fractions) {
        if (fractions.find(target) != fractions.end()) {
            return fractions[target];
        }

        int index = 2;
        int result = 0;
        while (index <= target) {
            int step = target / (target / index);
            result += (step - index + 1) * get_fractions(target / step, fractions);
            index = step + 1;
        }
        result = get_count(target) - result;
        fractions.insert(pair<int, int>(target, result));
        return result;
    }

    int get_count(int value) {
        int quotient = value / 6;
        int remainder = value % 6;
        if (5 == remainder) {
            return quotient * (quotient * 3 - 2 + remainder) + 1;
        }
        return quotient * (quotient * 3 - 2 + remainder);
    }
};

#include <iostream>
#include <unordered_map>
using namespace std;

class Problem072 {
public:
    void solution() {
        int target = 1000000;
        unordered_map<int, long long> fractions(0);
        fractions.insert(pair<int, long long>(1, get_summation(1)));
        long long result = get_fractions(target, fractions) - fractions[1];
        cout << result << endl;
    }

private:
    long long get_fractions(int target, unordered_map<int, long long> &fractions) {
        if (fractions.find(target) != fractions.end()) {
            return fractions[target];
        }

        int index = 2;
        long long result = 0L;
        while (index <= target) {
            int step = target / (target / index);
            result += (step - index + 1) * get_fractions(target / step, fractions);
            index = step + 1;
        }
        result = get_summation(target) - result;
        fractions.insert(pair<int, long long>(target, result));
        return result;
    }

    long long get_summation(int value) {
        return (long long) value * (value + 1) >> 1;
    }
};

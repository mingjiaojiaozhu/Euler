#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
using namespace std;

class Problem062 {
public:
    void solution() {
        int target = 5;
        unordered_map<long long, vector<long long>> cubes(0);
        int index = 5;
        int pivot = 0;
        while (true) {
            long long value = (long long) pow(index, 3);
            long long digits = get_digits(value);
            int count = (int) log10(value);
            if (pivot != count) {
                cubes.clear();
                pivot = count;
            } else {
                if (cubes.find(digits) != cubes.end() && (int) cubes[digits].size() == target - 1) {
                    cout << cubes[digits][0] << endl;
                    return;
                }
            }
            if (cubes.find(digits) == cubes.end()) {
                cubes.insert(pair<long long, vector<long long>>(digits, vector<long long>(0)));
            }
            cubes[digits].emplace_back(value);
            ++index;
        }
    }

private:
    long long get_digits(long long value) {
        long long result = 0L;
        while (value) {
            result += (long long) pow(10, value % 10);
            value /= 10;
        }
        return result;
    }
};

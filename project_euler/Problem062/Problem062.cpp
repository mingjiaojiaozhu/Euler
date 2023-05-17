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
            long long summation = get_summation(value);
            int digit = (int) log10(value);
            if (pivot != digit) {
                cubes.clear();
                pivot = digit;
            } else {
                if (cubes.find(summation) != cubes.end() && (int) cubes[summation].size() == target - 1) {
                    cout << cubes[summation][0] << endl;
                    return;
                }
            }
            if (cubes.find(summation) == cubes.end()) {
                cubes[summation] = vector<long long>(0);
            }
            cubes[summation].emplace_back(value);
            ++index;
        }
    }

private:
    long long get_summation(long long value) {
        long long result = 0L;
        while (value) {
            result += (long long) pow(10, value % 10);
            value /= 10;
        }
        return result;
    }
};

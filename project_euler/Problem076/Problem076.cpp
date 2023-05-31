#include <iostream>
#include <vector>
using namespace std;

class Problem076 {
public:
    void solution() {
        int target = 100;
        vector<int> ways(target + 1, 0);
        ways[0] = 1;
        for (int i = 1; i < target; ++i) {
            for (int j = i; j <= target; ++j) {
                ways[j] += ways[j - i];
            }
        }
        cout << ways[target] << endl;
    }
};

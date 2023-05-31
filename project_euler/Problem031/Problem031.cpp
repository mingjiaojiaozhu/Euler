#include <iostream>
#include <vector>
using namespace std;

class Problem031 {
public:
    void solution() {
        int target = 200;
        vector<int> coins = {1, 2, 5, 10, 20, 50, 100, 200};
        vector<int> ways(target + 1, 0);
        ways[0] = 1;
        for (int coin : coins) {
            for (int i = coin; i <= target; ++i) {
                ways[i] += ways[i - coin];
            }
        }
        cout << ways[target] << endl;
    }
};

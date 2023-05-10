#include <iostream>
#include <vector>
using namespace std;

class Problem031 {
public:
    void solution() {
        int target = 200;
        vector<int> coins = {1, 2, 5, 10, 20, 50, 100, 200};
        int result = get_ways(target, coins, (int) coins.size() - 1);
        cout << result << endl;
    }

private:
    int get_ways(int target, const vector<int> &coins, int index) {
        if (!target || !index) {
            return 1;
        }

        if (target < coins[index]) {
            return get_ways(target, coins, index - 1);
        }
        return get_ways(target, coins, index - 1) + get_ways(target - coins[index], coins, index);
    }
};

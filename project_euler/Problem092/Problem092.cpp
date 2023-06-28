#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
using namespace std;

class Problem092 {
public:
    void solution() {
        int target = 10000000;
        int border = 9 * 9 * (int) log10(target);
        unordered_set<int> chains(0);
        int pivot = 89;
        chains.insert(pivot);

        vector<int> squares(10);
        for (int i = 0; i < 10; ++i) {
            squares[i] = i * i;
        }

        int result = 0;
        for (int i = 1; i <= border; ++i) {
            if (get_chains(i, chains, pivot, squares)) {
                ++result;
            }
        }

        for (int i = border + 1; i < target; ++i) {
            if (chains.find(square_digits(i, squares)) != chains.end()) {
                ++result;
            }
        }
        cout << result << endl;
    }

private:
    bool get_chains(int value, unordered_set<int> &chains, int pivot, const vector<int> &squares) {
        if (chains.find(value) != chains.end() || pivot == value) {
            return true;
        }
        if (1 == value) {
            return false;
        }

        bool result = get_chains(square_digits(value, squares), chains, pivot, squares);
        if (result) {
            chains.insert(value);
        }
        return result;
    }

    int square_digits(int value, const vector<int> &squares) {
        int result = 0;
        while (value) {
            result += squares[value % 10];
            value /= 10;
        }
        return result;
    }
};

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Problem090 {
public:
    void solution() {
        vector<int> elements = {0, 1, 2, 3, 4, 5, 6, 7, 8, 6};
        vector<vector<int>> ways(0);
        vector<int> auxiliary(6);
        combination(elements, 0, 6, (int) elements.size(), ways, auxiliary, 0);

        vector<int> squares(0);
        for (int i = 1; i < 10; ++i) {
            squares.emplace_back(reverse_9_to_6(i * i));
        }

        int result = 0;
        unordered_set<int> arrangements(0);
        for (int i = (int) ways.size() - 1; i >= 0; --i) {
            for (int j = 0; j <= i; ++j) {
                if (check_digits(ways, i, j, squares, arrangements)) {
                    ++result;
                }
            }
        }
        cout << result << endl;
    }

private:
    void combination(const vector<int> &elements, int start, int count, int length, vector<vector<int>> &ways, vector<int> &auxiliary, int size) {
        if (count == size) {
            ways.emplace_back(vector<int>(auxiliary));
            return;
        }

        for (int i = start; i < length; ++i) {
            auxiliary[size] = elements[i];
            ++size;
            combination(elements, i + 1, count, length, ways, auxiliary, size);
            --size;
        }
    }

    int reverse_9_to_6(int value) {
        if (9 == value / 10) {
            value -= 30;
        }
        if (9 == value % 10) {
            value -= 3;
        }
        return value;
    }

    bool check_digits(const vector<vector<int>> &ways, int start, int end, vector<int> &squares, unordered_set<int> &arrangements) {
        arrangements.clear();
        for (int pivot : ways[start]) {
            for (int value : ways[end]) {
                arrangements.insert(pivot * 10 + value);
                arrangements.insert(value * 10 + pivot);
            }
        }

        for (int value : squares) {
            if (arrangements.find(value) == arrangements.end()) {
                return false;
            }
        }
        return true;
    }
};

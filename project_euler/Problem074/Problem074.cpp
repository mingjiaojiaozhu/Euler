#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
using namespace std;

class Problem074 {
public:
    void solution() {
        int target = 60;
        int border = 1000000;
        int step = (int) log10(border);
        vector<int> permutations(0);
        for (int i = 1; i < 10; ++i) {
            permutations.emplace_back(i);
        }
        unordered_set<int> chains(0);
        unordered_map<int, int> terms(0);
        vector<int> factorials(10);
        factorials[0] = 1;
        for (int i = 1; i < 10; ++i) {
            factorials[i] = factorials[i - 1] * i;
        }
        vector<int> counts(10);
        vector<int> auxiliary(0);
        int result = 0;
        for (int value : permutations) {
            if (target == get_terms(value, chains, terms, factorials, counts)) {
                result += get_permutations(value, factorials, counts);
            }
        }
        for (int i = 1; i < step; ++i) {
            get_digits(permutations, auxiliary);
            for (int value : permutations) {
                if (target == get_terms(value, chains, terms, factorials, counts)) {
                    result += get_permutations(value, factorials, counts);
                }
            }
        }
        cout << result << endl;
    }

private:
    int get_terms(int value, unordered_set<int> &chains, unordered_map<int, int> &terms, const vector<int> &factorials, vector<int> &counts) {
        chains.clear();
        int pivot = value;
        int result;
        while (true) {
            if (terms.find(value) != terms.end()) {
                result = (int) chains.size() + terms[value];
                break;
            }
            if (chains.find(value) != chains.end()) {
                result = (int) chains.size();
                break;
            }

            chains.insert(value);
            value = get_summation(value, factorials, counts);
        }
        terms.insert(pair<int, int>(pivot, result));
        return result;
    }

    int get_permutations(int value, const vector<int> &factorials, vector<int> &counts) {
        int length = 0;
        bool exists_0 = false;
        counts.assign(10, 0);
        while (value) {
            ++length;
            int remainder = value % 10;
            if (!remainder) {
                exists_0 = true;
            }
            ++counts[remainder];
            value /= 10;
        }

        int result = factorials[length];
        if (exists_0) {
            result = result * (length - 1) / length;
        }
        for (int i = 0; i < 10; ++i) {
            int count = counts[i];
            if (1 != count) {
                result /= factorials[count];
            }
        }
        return result;
    }

    void get_digits(vector<int> &permutations, vector<int> &auxiliary) {
        auxiliary.insert(auxiliary.end(), permutations.begin(), permutations.end());
        permutations.clear();
        for (int value : auxiliary) {
            int remainder = value % 10;
            for (int i = 0; i <= remainder; ++i) {
                permutations.emplace_back(value * 10 + i);
            }
        }
        auxiliary.clear();
    }

    int get_summation(int value, const vector<int> &factorials, vector<int> &counts) {
        int result = 0;
        while (value) {
            result += factorials[value % 10];
            value /= 10;
        }

        for (int i = 0; i < 10; ++i) {
            counts[i] = 0;
        }
        while (result) {
            ++counts[9 - result % 10];
            result /= 10;
        }

        for (int i = 0; i < 10; ++i) {
            int count = counts[i];
            for (int j = 0; j < count; ++j) {
                result = result * 10 + 9 - i;
            }
        }
        return result;
    }
};

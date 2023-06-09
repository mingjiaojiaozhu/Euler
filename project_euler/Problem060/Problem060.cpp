#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Problem060 {
public:
    void solution() {
        int target = 5;
        vector<int> primes(0);
        for (int i = 3; i < 10000; i += 2) {
            if (is_prime(i)) {
                primes.emplace_back(i);
            }
        }

        int length = (int) primes.size();
        vector<vector<int>> edges(length, vector<int>(length, 0));
        for (int i = 1; i < length; ++i) {
            int value = primes[i];
            if (check_prime(merge(3, value), primes) && check_prime(merge(value, 3), primes)) {
                edges[0][i] = 1;
                edges[i][0] = 1;
            }
        }
        for (int i = 1; i < length; ++i) {
            int pivot = primes[i];
            for (int j = i + 1; j < length; ++j) {
                int value = primes[j];
                if (pivot % 3 == value % 3 && check_prime(merge(pivot, value), primes) && check_prime(merge(value, pivot), primes)) {
                    edges[i][j] = 1;
                    edges[j][i] = 1;
                }
            }
        }

        vector<int> cliques(0);
        vector<int> indexes(0);
        for (int i = 0; i < length; ++i) {
            indexes.emplace_back(i);
        }
        search(primes, edges, cliques, indexes, target);
    }

private:
    bool is_prime(int value) {
        if (1 != value % 6 && 5 != value % 6) {
            return 2 == value || 3 == value;
        }

        int border = (int) sqrt(value);
        for (int i = 5; i <= border; i += 6) {
            if (!(value % i) || !(value % (i + 2))) {
                return false;
            }
        }
        return 1 != value;
    }

    bool check_prime(int value, const vector<int> &primes) {
        if (value < 10000) {
            int start = 0;
            int end = (int) primes.size() - 1;
            while (start <= end) {
                int current = start + ((end - start) >> 1);
                int prime = primes[current];
                if (prime == value) {
                    return true;
                }

                if (prime < value) {
                    start = current + 1;
                } else {
                    end = current - 1;
                }
            }
            return false;
        }

        int border = (int) sqrt(value);
        int start = 0;
        int end = (int) primes.size() - 1;
        while (start <= end) {
            int current = start + ((end - start) >> 1);
            if (primes[current] <= border) {
                start = current + 1;
            } else {
                end = current - 1;
            }
        }

        for (int i = 0; i < start; ++i) {
            if (!(value % primes[i])) {
                return false;
            }
        }
        return true;
    }

    int merge(int head, int tail) {
        return head * (int) pow(10, (int) log10(tail) + 1) + tail;
    }

    void search(const vector<int> &primes, const vector<vector<int>> &edges, vector<int> &cliques, vector<int> indexes, int target) {
        if (indexes.empty()) {
            if ((int) cliques.size() == target) {
                int result = 0;
                for (int index : cliques) {
                    result += primes[index];
                }
                cout << result << endl;
            }
            return;
        }

        int start = indexes[0];
        for (int i = (int) indexes.size() - 1; i >= 0; --i) {
            int index = indexes[i];
            if (!edges[start][index]) {
                cliques.emplace_back(index);
                search(primes, edges, cliques, get_adjacents(edges, indexes, index), target);
                cliques.pop_back();
                indexes.erase(find(indexes.begin(), indexes.end(), index));
            }
        }
    }

    vector<int> get_adjacents(const vector<vector<int>> &edges, vector<int> &indexes, int start) {
        vector<int> auxiliary(0);
        for (int index : indexes) {
            if (edges[start][index]) {
                auxiliary.emplace_back(index);
            }
        }
        return auxiliary;
    }
};

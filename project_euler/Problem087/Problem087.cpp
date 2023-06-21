#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
using namespace std;

class Problem087 {
public:
    void solution() {
        int target = 50000000;
        vector<vector<int>> primes(3, vector<int>(0));
        get_primes(primes, 2, 3);

        vector<int> borders = {(int) sqrt(target), (int) pow(target, (double) 1 / 3), (int) pow(target, (double) 1 / 4)};
        int index = 3;
        for (int i = 2; i >= 0; --i) {
            int size = i + 1;
            while (index < borders[i]) {
                if (is_prime(index)) {
                    get_primes(primes, index, size);
                }
                index += 2;
            }
        }

        unordered_set<int> summations(0);
        for (int prime : primes[2]) {
            int pivot = target - prime;
            int border = get_index(pivot, primes[1]);
            for (int i = 0; i < border; ++i) {
                int value = primes[1][i];
                int end = get_index(pivot - value, primes[0]);
                for (int j = 0; j < end; ++j) {
                    summations.insert(prime + value + primes[0][j]);
                }
            }
        }
        cout << (int) summations.size() << endl;
    }

private:
    void get_primes(vector<vector<int>> &primes, int pivot, int size) {
        int value = pivot;
        for (int i = 0; i < size; ++i) {
            value *= pivot;
            primes[i].emplace_back(value);
        }
    }

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

    int get_index(int value, const vector<int> &primes) {
        int start = 0;
        int end = (int) primes.size() - 1;
        while (start <= end) {
            int current = start + ((end - start) >> 1);
            if (primes[current] <= value) {
                start = current + 1;
            } else {
                end = current - 1;
            }
        }
        return start;
    }
};

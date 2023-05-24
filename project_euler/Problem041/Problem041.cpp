#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Problem041 {
public:
    void solution() {
        vector<int> elements = {7, 6, 5, 4, 3, 2, 1};
        int result = permutation(elements, 0, (int) elements.size(), 0);
        cout << result << endl;
    }

private:
    int permutation(vector<int> &elements, int index, int length, int pivot) {
        if (index == length) {
            int result = 0L;
            for (int element : elements) {
                result = result * 10 + element;
            }
            if (is_prime(result)) {
                return max(result, pivot);
            }
            return pivot;
        }

        int result = permutation(elements, index + 1, length, pivot);
        for (int i = index + 1; i < length; ++i) {
            swap(elements[index], elements[i]);
            result = permutation(elements, index + 1, length, result);
            swap(elements[index], elements[i]);
        }
        return result;
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
};

#include <iostream>
#include <vector>
using namespace std;

class Problem024 {
public:
    void solution() {
        long long target = 1000000L;
        vector<int> elements = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        permutation(target - 1, elements, (int) elements.size(), 0);

        long long result = 0L;
        for (int element : elements) {
            result = result * 10 + element;
        }
        cout << result << endl;
    }

private:
    void permutation(long long sequence, vector<int> &elements, int length, int start) {
        if (1 == length - start) {
            return;
        }

        long long count = get_factorial(length - start - 1);
        int index = (int) (sequence / count) + start;
        if (index != start) {
            int auxiliary = elements[index];
            copy(elements.begin() + start, elements.begin() + index, elements.begin() + start + 1);
            elements[start] = auxiliary;
        }
        ++start;
        permutation(sequence % count, elements, length, start);
    }

    long long get_factorial(int value) {
        long long result = 1L;
        for (int i = 2; i <= value; ++i) {
            result *= i;
        }
        return result;
    }
};

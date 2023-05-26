#include <iostream>
#include <vector>
using namespace std;

class Problem043 {
public:
    void solution() {
        vector<int> elements(10);
        elements[5] = 5;
        vector<bool> digits(10, false);
        digits[5] = true;

        int start = 500;
        while (start % 11) {
            ++start;
        }

        long long result = 0L;
        for (int i = start; i < 600; i += 11) {
            elements[6] = (i % 100) / 10;
            elements[7] = i % 10;
            if (5 != elements[6] && 5 != elements[7] && elements[6] != elements[7]) {
                digits[elements[6]] = true;
                digits[elements[7]] = true;
                result += check13(elements, elements[6] * 100 + elements[7] * 10, digits);
                digits[elements[6]] = false;
                digits[elements[7]] = false;
            }
        }
        cout << result << endl;
    }

private:
    long long check13(vector<int> &elements, int pivot, vector<bool> &digits) {
        long long result = 0L;
        for (int i = 0; i < 10; ++i) {
            if (!digits[i] && !((pivot + i) % 13)) {
                elements[8] = i;
                digits[i] = true;
                result += check17(elements, ((pivot + i) % 100) * 10, digits);
                digits[i] = false;
            }
        }
        return result;
    }

    long long check17(vector<int> &elements, int pivot, vector<bool> &digits) {
        long long result = 0L;
        for (int i = 0; i < 10; ++i) {
            if (!digits[i] && !((pivot + i) % 17)) {
                elements[9] = i;
                digits[i] = true;
                fill(elements, digits);
                result += permutation(elements, 0, 5);
                digits[i] = false;
            }
        }
        return result;
    }

    void fill(vector<int> &elements, const vector<bool> &digits) {
        int index = 4;
        for (int i = (int) digits.size() - 1; i >= 0; --i) {
            if (!digits[i]) {
                elements[index] = i;
                --index;
            }
        }
    }

    long long permutation(vector<int> &elements, int index, int length) {
        if (index == length) {
            if (!elements[0] || (elements[3] & 1) || (elements[2] + elements[3] + elements[4]) % 3 || (10 * elements[4] + elements[5] - (elements[6] << 1)) % 7) {
                return 0L;
            }

            long long result = 0L;
            for (int element : elements) {
                result = result * 10 + element;
            }
            return result;
        }

        long long result = permutation(elements, index + 1, length);
        for (int i = index + 1; i < length; ++i) {
            swap(elements[index], elements[i]);
            result += permutation(elements, index + 1, length);
            swap(elements[index], elements[i]);
        }
        return result;
    }
};

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Problem036 {
public:
    void solution() {
        int target = 1000000;
        int border = (int) ceil(sqrt(target));
        vector<int> palindromes(2);
        vector<bool> binary(0);

        int result = 0;
        for (int i = 1; i < border; ++i) {
            get_palindrome(i, palindromes);
            if (is_binary_palindrome(palindromes[0], binary)) {
                result += palindromes[0];
            }
            if (is_binary_palindrome(palindromes[1], binary)) {
                result += palindromes[1];
            }
        }
        cout << result << endl;
    }

private:
    void get_palindrome(int value, vector<int> &palindromes) {
        palindromes[0] = value / 10;
        palindromes[1] = value;
        while (value) {
            palindromes[0] = palindromes[0] * 10 + value % 10;
            palindromes[1] = palindromes[1] * 10 + value % 10;
            value /= 10;
        }
    }

    bool is_binary_palindrome(int value, vector<bool> &binary) {
        binary.clear();
        while (value) {
            binary.emplace_back(value & 1);
            value >>= 1;
        }

        int start = 0;
        int end = (int) binary.size() - 1;
        while (start < end) {
            if (binary[start] ^ binary[end]) {
                return false;
            }
            ++start;
            --end;
        }
        return true;
    }
};

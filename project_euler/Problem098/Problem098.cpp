#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

class Problem098 {
public:
    void solution() {
        string file_name = "words.txt";
        vector<vector<string>> word_pairs(0);
        int length = get_word_pair(file_name, word_pairs);

        vector<unordered_set<long long>> squares(length - 2, unordered_set<long long>(0));
        get_squares(squares, length);

        long long result = 0L;
        vector<int> letters(26);
        vector<char> digits(10);
        for (vector<string> words : word_pairs) {
            int size = (int) words[0].size();
            unordered_set<long long> auxiliary = squares[size - 3];
            for (long long pivot : auxiliary) {
                if (set_digits(words[0], pivot, letters, digits, size)) {
                    long long value = get_digits(words[1], letters);
                    if (auxiliary.find(value) != auxiliary.end() && (result < value || result < pivot)) {
                        result = max(value, pivot);
                    }
                }
            }
        }
        cout << result << endl;
    }

private:
    int get_word_pair(const string &file_name, vector<vector<string>> &word_pairs) {
        vector<string> auxiliary(0);
        fstream handle(file_name, ios::in);
        string line;
        while (getline(handle, line)) {
            if ((int) line.size() > 2) {
                auxiliary.emplace_back(line);
            }
        }
        handle.close();

        vector<vector<int>> letters(2, vector<int>(26));
        int result = 0;
        for (int i = (int) auxiliary.size() - 1; i > 0; --i) {
            string pivot = auxiliary[i];
            get_letters(pivot, letters[0]);
            int length = (int) pivot.size();
            bool is_pair = false;
            for (int j = 0; j < i; ++j) {
                string word = auxiliary[j];
                if (length == (int) word.size()) {
                    get_letters(word, letters[1]);
                    if (check_letters(letters)) {
                        word_pairs.emplace_back(vector<string>{word, pivot});
                        is_pair = true;
                    }
                }
            }
            if (is_pair && result < length) {
                result = length;
            }
        }
        return result;
    }

    void get_squares(vector<unordered_set<long long>> &squares, int length) {
        long long border = (long long) pow(10, length);
        int size = 2;
        long long index = 10L;
        while (true) {
            long long value = index * index;
            if (value >= border) {
                break;
            }

            if (size != (int) log10(value)) {
                ++size;
            }
            squares[size - 2].insert(value);
            ++index;
        }
    }

    bool set_digits(const string &word, long long value, vector<int> &letters, vector<char> &digits, int length) {
        letters.assign(26, -1);
        digits.assign(10, ' ');
        for (int i = length - 1; i >= 0; --i) {
            char letter = word[i];
            int index = letter - 'A';
            int remainder = (int) (value % 10);
            if ((-1 != letters[index] && remainder != letters[index]) || (' ' != digits[remainder] && index != digits[remainder])) {
                return false;
            }
            letters[index] = remainder;
            digits[remainder] = letter;
            value /= 10;
        }
        return true;
    }

    long long get_digits(const string &word, const vector<int> &letters) {
        long long result = 0L;
        for (char letter : word) {
            result = result * 10 + letters[letter - 'A'];
        }
        return result;
    }

    void get_letters(const string &word, vector<int> &letters) {
        letters.assign(26, 0);
        for (char letter : word) {
            ++letters[letter - 'A'];
        }
    }

    bool check_letters(const vector<vector<int>> &letters) {
        for (int i = 0; i < 26; ++i) {
            if (letters[0][i] != letters[1][i]) {
                return false;
            }
        }
        return true;
    }
};

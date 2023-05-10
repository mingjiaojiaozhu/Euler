#include <iostream>
#include <vector>
using namespace std;

class Problem017 {
public:
    void solution() {
        vector<int> letters_below_10 = {3, 3, 5, 4, 4, 3, 5, 5, 4};
        vector<int> letters_10_to_19 = {3, 6, 6, 8, 8, 7, 7, 9, 8, 8};
        vector<int> letters_whole_ten = {6, 6, 5, 5, 5, 7, 6, 6};
        int letter_100 = 7;
        int letter_and = 3;
        int letter_1000 = 8;

        int count_below_10 = 0;
        for (int letter : letters_below_10) {
            count_below_10 += letter;
        }

        int count_below_100 = count_below_10 * 9;
        for (int letter : letters_10_to_19) {
            count_below_100 += letter;
        }
        for (int letter : letters_whole_ten) {
            count_below_100 += letter * 10;
        }

        int result = count_below_100 * 10 + count_below_10 * 100 + letter_100 * 100 * 9 + letter_and * 99 * 9 + letters_below_10[0] + letter_1000;
        cout << result << endl;
    }
};

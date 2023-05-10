#include <iostream>
#include <vector>
using namespace std;

class Problem019 {
public:
    void solution() {
        int start = 1900;
        int end = 2000;
        vector<int> days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int length = (int) days.size();

        int week = 1;
        for (int day : days) {
            week += day;
        }
        if (!(start % 4) && (start % 100 || !(start % 400))) {
            ++week;
        }
        week %= 7;

        int result = 0;
        for (int i = start + 1; i <= end; ++i) {
            for (int j = 0; j < length; ++j) {
                if (!week) {
                    ++result;
                }

                week += days[j];
                if (1 == j && (!(start % 4) && (start % 100 || !(start % 400)))) {
                    ++week;
                }
                week %= 7;
            }
        }
        cout << result << endl;
    }
};

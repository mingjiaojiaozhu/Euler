#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Problem029 {
public:
    void solution() {
        int start = 2;
        int end = 100;
        vector<double> terms(0);
        for (int i = start; i <= end; ++i) {
            for (int j = start; j <= end; ++j) {
                terms.emplace_back(i * log(j));
            }
        }

        sort(terms.begin(), terms.end());

        int result = (int) terms.size();
        for (int i = result - 1; i >= 1; --i) {
            if (fabs(terms[i] - terms[i - 1]) < 0.00000001) {
                --result;
            }
        }
        cout << result << endl;
    }
};

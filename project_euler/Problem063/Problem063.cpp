#include <iostream>
#include <cmath>
using namespace std;

class Problem063 {
public:
    void solution() {
        int result = 0;
        for (int i = 1; i < 10; ++i) {
            result += (int) (1.0 / (1 - log10(i)));
        }
        cout << result << endl;
    }
};

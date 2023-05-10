#include <iostream>
#include <cmath>
using namespace std;

class Problem025 {
public:
    void solution() {
        int target = 1000;
        int result = (int) ceil(((double) target - 1 + log10(5) / 2) / log10((1 + sqrt(5)) / 2));
        cout << result << endl;
    }
};

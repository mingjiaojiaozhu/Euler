#include <iostream>
using namespace std;

class Problem100 {
public:
    void solution() {
        long long target = 1000000000000L;
        long long index = 1L;
        long long result = 1L;
        while (index < target) {
            long long auxiliary = (index << 1) + result * 3 - 2;
            index = index * 3 + (result << 2) - 3;
            result = auxiliary;
        }
        cout << result << endl;
    }
};

#include <iostream>
using namespace std;

class Problem071 {
public:
    void solution() {
        int target = 1000000;
        int index = (target - 5) / 7;
        int result = index * 3 + 2;
        cout << result << endl;
    }
};

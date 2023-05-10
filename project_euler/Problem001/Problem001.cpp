#include <iostream>
using namespace std;

class Problem001 {
public:
    void solution() {
        int target = 1000;
        int result = get_summation(target, 3) + get_summation(target, 5) - get_summation(target, 3 * 5);
        cout << result << endl;
    }

private:
    int get_summation(int border, int factor) {
        int count = (border - 1) / factor;
        return factor * count * (count + 1) >> 1;
    }
};

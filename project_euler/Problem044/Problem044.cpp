#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Problem044 {
public:
    void solution() {
        vector<int> pentagons(0);
        int index = 1;
        while (true) {
            int current = index * (3 * index - 1) >> 1;
            for (int pentagon : pentagons) {
                if (is_pentagon(current + pentagon) && is_pentagon(current - pentagon)) {
                    cout << current - pentagon << endl;
                    return;
                }
            }
            pentagons.emplace_back(current);
            ++index;
        }
    }

private:
    bool is_pentagon(int value) {
        int delta = value * 24 + 1;
        return fabs(floor(sqrt(delta) + 0.5) - sqrt(delta)) < 0.00000001 && !(((int) sqrt(delta) + 1) % 6);
    }
};

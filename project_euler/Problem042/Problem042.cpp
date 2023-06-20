#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

class Problem042 {
public:
    void solution() {
        string file_name = "words.txt";
        int result = 0;
        fstream handle(file_name, ios::in);
        string line;
        while (getline(handle, line)) {
            int value = 0;
            for (char letter : line) {
                value += letter - 'A' + 1;
            }
            double auxiliary = sqrt((value << 3) + 1);
            if (fabs(floor(auxiliary + 0.5) - auxiliary) < 0.00000001 && ((int) auxiliary & 1)) {
                ++result;
            }
        }
        handle.close();
        cout << result << endl;
    }
};

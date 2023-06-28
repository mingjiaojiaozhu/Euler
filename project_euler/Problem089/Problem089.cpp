#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Problem089 {
public:
    void solution() {
        string file_name = "roman.txt";
        fstream handle(file_name, ios::in);
        string line;
        int result = 0;
        while (getline(handle, line)) {
            char previous = ' ';
            char pivot = ' ';
            int count = 1;
            for (char value : line) {
                if (pivot == value) {
                    ++count;
                } else {
                    previous = pivot;
                    pivot = value;
                    count = 1;
                }

                if (count >= 4) {
                    if (('I' == pivot && 'V' == previous) || ('X' == pivot && 'L' == previous) || ('C' == pivot && 'D' == previous)) {
                        result += 3;
                    } else if ('M' != pivot) {
                        result += 2;
                    }
                }
            }
        }
        handle.close();
        cout << result << endl;
    }
};

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

class Problem099 {
public:
    void solution() {
        string file_name = "base_exp.txt";
        fstream handle(file_name, ios::in);
        string line;
        int index = 1;
        double pivot = 0;
        int result = 0;
        while (getline(handle, line)) {
            vector<string> elements = split(line, ' ');
            double value = log(stoi(elements[0])) * stoi(elements[1]);
            if (pivot < value) {
                pivot = value;
                result = index;
            }
            ++index;
        }
        handle.close();
        cout << result << endl;
    }

private:
    vector<string> split(const string &line, const char delimiter) {
        size_t previous = 0;
        size_t current = line.find(delimiter);
        vector<string> elements(0);
        while (current != string::npos) {
            elements.emplace_back(line.substr(previous, current - previous));
            previous = current + 1;
            current = line.find(delimiter, previous);
        }
        if (previous != line.size()) {
            elements.emplace_back(line.substr(previous));
        }
        return elements;
    }
};

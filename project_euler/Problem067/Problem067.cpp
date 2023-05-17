#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Problem067 {
public:
    void solution() {
        string file_name = "triangle.txt";
        int border = 100;
        vector<vector<int>> target(border, vector<int>(border));

        fstream handle(file_name, ios::in);
        string line;
        int index = 0;
        while (getline(handle, line)) {
            vector<string> elements = split(line, ' ');
            for (int i = (int) elements.size() - 1; i >= 0; --i) {
                target[index][i] = stoi(elements[i]);
            }
            ++index;
        }
        handle.close();

        for (int i = border - 1; i > 0; --i) {
            for (int j = i - 1; j >= 0; --j) {
                target[i - 1][j] += max(target[i][j], target[i][j + 1]);
            }
        }
        cout << target[0][0] << endl;
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

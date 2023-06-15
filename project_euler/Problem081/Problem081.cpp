#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Problem081 {
public:
    void solution() {
        string file_name = "matrix.txt";
        int border = 80;
        vector<vector<int>> target(border, vector<int>(border));

        fstream handle(file_name, ios::in);
        string line;
        int index = 0;
        while (getline(handle, line)) {
            vector<string> elements = split(line, ' ');
            for (int i = 0; i < border; ++i) {
                target[index][i] = stoi(elements[i]);
            }
            ++index;
        }
        handle.close();

        for (int i = 1; i < border; ++i) {
            target[0][i] += target[0][i - 1];
            target[i][0] += target[i - 1][0];
        }
        for (int i = 1; i < border; ++i) {
            for (int j = 1; j < border; ++j) {
                target[i][j] += min(target[i - 1][j], target[i][j - 1]);
            }
        }
        cout << target[border - 1][border - 1] << endl;
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

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Problem082 {
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

        vector<int> ways(border);
        for (int i = 0; i < border; ++i) {
            ways[i] = target[i][border - 1];
        }
        for (int i = border - 2; i >= 0; --i) {
            ways[0] += target[0][i];
            for (int j = 1; j < border; ++j) {
                if (ways[j] > ways[j - 1]) {
                    ways[j] = ways[j - 1] + target[j][i];
                } else {
                    ways[j] += target[j][i];
                }
            }
            for (int j = border - 2; j >= 0; --j) {
                if (ways[j] > ways[j + 1] + target[j][i]) {
                    ways[j] = ways[j + 1] + target[j][i];
                }
            }
        }

        int result = ways[0];
        for (int value : ways) {
            if (result > value) {
                result = value;
            }
        }
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

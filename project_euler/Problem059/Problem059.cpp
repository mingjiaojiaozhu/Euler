#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
using namespace std;

class Problem059 {
public:
    void solution() {
        string file_name = "cipher.txt";
        vector<int> codes(0);
        vector<unordered_map<int, int>> counts(3, unordered_map<int, int>(0));

        fstream handle(file_name, ios::in);
        string line;
        int index = 0;
        while (getline(handle, line)) {
            int code = stoi(line);
            codes.emplace_back(code);
            if (counts[index].find(code) != counts[index].end()) {
                ++counts[index][code];
            } else {
                counts[index].insert(pair<int, int>(code, 1));
            }
            ++index;
            if (3 == index) {
                index = 0;
            }
        }
        handle.close();

        vector<int> keys(3);
        for (int i = 0; i < 3; ++i) {
            int pivot = 0;
            for (pair<const int, int> p : counts[i]) {
                if (pivot < p.second) {
                    pivot = p.second;
                    keys[i] = p.first;
                }
            }
            keys[i] ^= ' ';
        }

        int result = 0;
        index = 0;
        for (int code : codes) {
            result += code ^ keys[index];
            ++index;
            if (3 == index) {
                index = 0;
            }
        }
        cout << result << endl;
    }
};

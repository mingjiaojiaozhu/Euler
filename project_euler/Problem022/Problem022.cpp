#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

class Problem022 {
public:
    void solution() {
        string file_name = "names.txt";
        vector<string> names(0);

        fstream handle(file_name, ios::in);
        string line;
        while (getline(handle, line)) {
            names.emplace_back(line);
        }
        handle.close();

        sort(names.begin(), names.end());

        long long result = 0L;
        for (int i = (int) names.size() - 1; i >= 0; --i) {
            int score = 0;
            for (char letter : names[i]) {
                score += letter - 'A' + 1;
            }
            result += (long long) score * (i + 1);
        }
        cout << result << endl;
    }
};

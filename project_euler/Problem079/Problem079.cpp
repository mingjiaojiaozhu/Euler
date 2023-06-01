#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Problem079 {
public:
    void solution() {
        string file_name = "keylog.txt";
        int length = 10;
        vector<vector<int>> elements(length, vector<int>(length, 0));
        vector<bool> visited(length, true);

        fstream handle(file_name, ios::in);
        string line;
        while (getline(handle, line)) {
            create_elements(stoi(line), elements, visited);
        }
        handle.close();

        vector<int> digits(0);
        for (int i = 0; i < length; ++i) {
            if (!visited[i]) {
                search(elements, i, digits, visited, length);
            }
        }

        int result = 0;
        for (int i = (int) digits.size() - 1; i >= 0; --i) {
            result = result * 10 + digits[i];
        }
        printf("%d\n", result);
    }

private:
    void create_elements(int value, vector<vector<int>> &elements, vector<bool> &visited) {
        int tail = value % 10;
        visited[tail] = false;
        while (value >= 10) {
            value /= 10;
            int head = value % 10;
            elements[head][tail] = 1;
            tail = head;
            visited[tail] = false;
        }
    }

    void search(const vector<vector<int>> &elements, int start, vector<int> &digits, vector<bool> &visited, int length) {
        visited[start] = true;
        vector<int> element = elements[start];
        for (int i = 0; i < length; ++i) {
            if (element[i] && !visited[i]) {
                search(elements, i, digits, visited, length);
            }
        }
        digits.emplace_back(start);
    }
};

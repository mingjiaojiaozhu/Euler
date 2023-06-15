#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <fstream>
using namespace std;

class Problem083 {
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

        int length = border * border;
        vector<vector<int>> edges(length, vector<int>(length, 0));
        for (int i = 0; i < border; ++i) {
            for (int j = 0; j < border; ++j) {
                if (i > 0) {
                    edges[i * border + j][(i - 1) * border + j] = target[i - 1][j];
                }
                if (j > 0) {
                    edges[i * border + j][i * border + j - 1] = target[i][j - 1];
                }
                if (i < border - 1) {
                    edges[i * border + j][(i + 1) * border + j] = target[i + 1][j];
                }
                if (j < border - 1) {
                    edges[i * border + j][i * border + j + 1] = target[i][j + 1];
                }
            }
        }

        vector<int> ways(length);
        search(edges, length, ways);
        cout << ways[length - 1] + target[0][0] << endl;
    }

private:
    struct Heap {
        int index;
        int weight;

        Heap(int index, int weight) : index(index), weight(weight) {}

        friend bool operator < (Heap p, Heap q) {
            return p.weight > q.weight;
        }
    };

    void search(const vector<vector<int>> &edges, int length, vector<int> &ways) {
        vector<bool> visited(length, false);
        priority_queue<Heap> queue;
        queue.push(Heap(0, 0));
        while (!queue.empty()) {
            Heap node = queue.top();
            queue.pop();
            int index = node.index;
            int weight = node.weight;
            if (visited[index]) {
                continue;
            }

            ways[index] = weight;
            visited[index] = true;
            for (int i = 0; i < length; ++i) {
                if (edges[index][i] && !visited[i]) {
                    queue.push(Heap(i, weight + edges[index][i]));
                }
            }
        }
    }

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

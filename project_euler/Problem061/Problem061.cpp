#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Problem061 {
public:
    void solution() {
        int target = 6;
        vector<Polygonal *> polygonals(0);
        add_triangle(polygonals);
        add_square(polygonals);
        add_pentagonal(polygonals);
        add_hexagonal(polygonals);
        add_heptagonal(polygonals);
        add_octagonal(polygonals);

        int length = (int) polygonals.size();
        vector<vector<int>> edges(length, vector<int>(length, 0));
        for (int i = 0; i < length; ++i) {
            Polygonal *pivot = polygonals[i];
            for (int j = i + 1; j < length; ++j) {
                Polygonal *polygonal = polygonals[j];
                if (pivot->step != polygonal->step) {
                    if (pivot->tail == polygonal->head) {
                        edges[i][j] = 1;
                    }
                    if (polygonal->tail == pivot->head) {
                        edges[j][i] = 1;
                    }
                }
            }
        }

        vector<int> indexes(0);
        vector<bool> steps(target, false);
        int pivot = polygonals[0]->step;
        steps[pivot] = true;
        for (int i = 0; i < length; ++i) {
            indexes.emplace_back(i);
            int step = polygonals[i]->step;
            if (step != pivot) {
                return;
            }
            search(polygonals, edges, i, indexes, steps, target);
            indexes.pop_back();
        }
    }

private:
    struct Polygonal {
        int head;
        int tail;
        int step;

        Polygonal(int value, int step): head(value / 100), tail(value % 100), step(step) {}
    };

    void add_triangle(vector<Polygonal *> &polygonals) {
        int index = (int) ceil((sqrt(8001) - 1) / 2);
        while (true) {
            int value = index * (index + 1) >> 1;
            if (value >= 10000) {
                return;
            }
            if (value % 100 >= 10) {
                polygonals.emplace_back(new Polygonal(value, 0));
            }
            ++index;
        }
    }

    void add_square(vector<Polygonal *> &polygonals) {
        int index = (int) ceil(sqrt(1000));
        while (true) {
            int value = index * index;
            if (value >= 10000) {
                return;
            }
            if (value % 100 >= 10) {
                polygonals.emplace_back(new Polygonal(value, 1));
            }
            ++index;
        }
    }

    void add_pentagonal(vector<Polygonal *> &polygonals) {
        int index = (int) ceil((sqrt(24001) + 1) / 6);
        while (true) {
            int value = index * (3 * index - 1) >> 1;
            if (value >= 10000) {
                return;
            }
            if (value % 100 >= 10) {
                polygonals.emplace_back(new Polygonal(value, 2));
            }
            ++index;
        }
    }

    void add_hexagonal(vector<Polygonal *> &polygonals) {
        int index = (int) ceil((sqrt(8001) + 1) / 4);
        while (true) {
            int value = index * ((index << 1) - 1);
            if (value >= 10000) {
                return;
            }
            if (value % 100 >= 10) {
                polygonals.emplace_back(new Polygonal(value, 3));
            }
            ++index;
        }
    }

    void add_heptagonal(vector<Polygonal *> &polygonals) {
        int index = (int) ceil((sqrt(40009) + 3) / 10);
        while (true) {
            int value = index * (5 * index - 3) >> 1;
            if (value >= 10000) {
                return;
            }
            if (value % 100 >= 10) {
                polygonals.emplace_back(new Polygonal(value, 4));
            }
            ++index;
        }
    }

    void add_octagonal(vector<Polygonal *> &polygonals) {
        int index = (int) ceil((sqrt(12002) + 2) / 6);
        while (true) {
            int value = index * (3 * index - 2);
            if (value >= 10000) {
                return;
            }
            if (value % 100 >= 10) {
                polygonals.emplace_back(new Polygonal(value, 5));
            }
            ++index;
        }
    }

    void search(const vector<Polygonal *> &polygonals, const vector<vector<int>> &edges, int start, vector<int> &indexes, vector<bool> &steps, int target) {
        if ((int) indexes.size() == target) {
            if (polygonals[indexes[0]]->head == polygonals[indexes[target - 1]]->tail) {
                int result = 0;
                for (int index : indexes) {
                    Polygonal *polygonal = polygonals[index];
                    result += polygonal->head * 100 + polygonal->tail;
                }
                cout << result << endl;
            }
            return;
        }

        for (int i = (int) polygonals.size() - 1; i >= 0; --i) {
            if (edges[start][i]) {
                int step = polygonals[i]->step;
                if (!steps[step]) {
                    indexes.emplace_back(i);
                    steps[step] = true;
                    search(polygonals, edges, i, indexes, steps, target);
                    indexes.pop_back();
                    steps[step] = false;
                }
            }
        }
    }
};

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Problem084 {
public:
    void solution() {
        int target = 4;
        int length = 40;
        vector<vector<double>> dice(length, vector<double>(length, 0));
        set_dice(dice, length, target);

        vector<vector<double>> card(length, vector<double>(length, 0));
        set_card(card, length);

        vector<double> probability(length);
        set_probability(probability, dice, card, length);

        int size = 3;
        vector<Square *> squares(3);
        set_squares(squares, probability, length, size);

        int result;
        if (squares[1]->value > squares[2]->value) {
            result = squares[1]->index * 100 + squares[2]->index;
        } else {
            result = squares[2]->index * 100 + squares[1]->index;
        }
        result = result * 100 + squares[0]->index;
        cout << result << endl;
    }

private:
    struct Square {
        int index;
        double value;

        Square(int index, double value) : index(index), value(value) {}
    };

    void set_dice(vector<vector<double>> &dice, int length, int target) {
        int border = (target << 1) - 1;
        vector<double> chances(border);

        int start = 0;
        int end = border - 1;
        int count = 1;
        int total = target * target;
        while (start < end) {
            double chance = (double) count / total;
            chances[start] = chance;
            chances[end] = chance;
            ++count;
            ++start;
            --end;
        }
        chances[start] = (double) count / total;

        for (int i = length - border - 2; i >= 0; --i) {
            copy(chances.begin(), chances.end(), dice[i].begin() + i + 2);
        }
        for (int i = length - border - 1; i < length - 2; ++i) {
            copy(chances.begin(), chances.begin() + length - i - 2, dice[i].begin() + i + 2);
            copy(chances.begin() + length - i - 2, chances.end(), dice[i].begin());
        }
        for (int i = length - 2; i < length; ++i) {
            copy(chances.begin(), chances.end(), dice[i].begin() + i - length + 2);
        }
    }

    void set_card(vector<vector<double>> &card, int length) {
        for (int i = 0; i < length; ++i) {
            card[i][i] = 1;
        }
        set_jail(card, 30);
        set_community_chest(card, 2);
        set_community_chest(card, 17);
        set_community_chest(card, 33);
        set_chance(card, 7);
        set_chance(card, 22);
        set_chance(card, 36);
    }

    void set_probability(vector<double> &probability, const vector<vector<double>> &dice, const vector<vector<double>> &card, int length) {
        vector<vector<double>> board(length, vector<double>(length, 0));
        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < length; ++j) {
                for (int k = 0; k < length; ++k) {
                    board[i][j] += dice[i][k] * card[k][j];
                }
            }
        }

        vector<double> auxiliary(board[0].begin(), board[0].end());
        while (true) {
            probability.assign(length, 0);
            for (int i = 0; i < length; ++i) {
                for (int j = 0; j < length; ++j) {
                    probability[i] += auxiliary[j] * board[j][i];
                }
            }

            bool isSame = true;
            for (int i = 0; i < length; ++i) {
                if (fabs(probability[i] - auxiliary[i]) > 0.00001) {
                    isSame = false;
                    break;
                }
            }
            if (isSame) {
                return;
            }
            copy(probability.begin(), probability.end(), auxiliary.begin());
        }
    }

    void set_squares(vector<Square *> &squares, const vector<double> &probability, int length, int size) {
        for (int i = 0; i < size; ++i) {
            squares[i] = new Square(i, probability[i]);
        }
        adjust(squares);
        for (int i = size; i < length; ++i) {
            double value = probability[i];
            if (squares[0]->value < value) {
                squares[0]->index = i;
                squares[0]->value = value;
                adjust(squares);
            }
        }
    }

    void set_jail(vector<vector<double>> &card, int index) {
        card[index][10] = 1;
        card[index][index] = 0;
    }

    void set_community_chest(vector<vector<double>> &card, int index) {
        double chance = (double) 1 / 16;
        card[index][0] = chance;
        card[index][10] = chance;
        card[index][index] -= chance * 2;
    }

    void set_chance(vector<vector<double>> &card, int index) {
        double chance = (double) 1 / 16;
        card[index][0] = chance;
        card[index][10] = chance;
        card[index][11] = chance;
        card[index][24] = chance;
        card[index][39] = chance;
        card[index][5] = chance;

        int railway = 15;
        int utility = 12;
        if (22 == index) {
            railway = 25;
            utility = 28;
        } else if (36 == index) {
            railway = 5;
        }
        card[index][railway] += chance * 2;
        card[index][utility] += chance;
        card[index][index - 3] += chance;
        card[index][index] -= chance * 10;
    }

    void adjust(vector<Square *> &squares) {
        int pivot = 1;
        if (squares[1]->value > squares[2]->value) {
            pivot = 2;
        }

        if (squares[0]->value > squares[pivot]->value) {
            swap(squares[0], squares[pivot]);
        }
    }
};

#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

class Problem054 {
public:
    void solution() {
        string file_name = "poker.txt";
        vector<Player *> players(2);
        for (int i = 0; i < 2; ++i) {
            players[i] = new Player();
        }
        vector<int> counts(2);
        vector<int> pairs(2);

        fstream handle(file_name, ios::in);
        string line;
        int result = 0;
        while (getline(handle, line)) {
            vector<string> elements = split(line, ' ');
            set_cards(players[0], elements, 0, counts, pairs);
            set_cards(players[1], elements, 5, counts, pairs);
            if (is_winner(players)) {
                ++result;
            }
        }
        handle.close();
        cout << result << endl;
    }

private:
    struct Player {
        vector<int> value;
        unordered_set<char> suits;
        int hand;
        vector<int> ranks;

        Player(): value(vector<int>(5)), suits(unordered_set<char>(0)), hand(0), ranks(vector<int>(0)) {}
    };

    void set_cards(Player *player, const vector<string> &elements, int start, vector<int> &counts, vector<int> &pairs) {
        player->suits.clear();
        player->ranks.clear();

        for (int i = 0; i < 5; ++i) {
            string value = elements[start + i];
            player->value[i] = get_value(value[0]);
            player->suits.insert(value[1]);
        }
        sort(player->value.begin(), player->value.end());
        set_head(player, counts, pairs);
    }

    bool is_winner(vector<Player *> &players) {
        if (players[0]->hand != players[1]->hand) {
            return players[0]->hand < players[1]->hand;
        }

        int length = (int) players[0]->ranks.size();
        for (int i = 0; i < length; ++i) {
            if (players[0]->ranks[i] != players[1]->ranks[i]) {
                return players[0]->ranks[i] > players[1]->ranks[i];
            }
        }
        return true;
    }

    int get_value(char value) {
        if ('A' == value) {
            return 14;
        }
        if ('K' == value) {
            return 13;
        }
        if ('Q' == value) {
            return 12;
        }
        if ('J' == value) {
            return 11;
        }
        if ('T' == value) {
            return 10;
        }
        return value - '0';
    }

    void set_head(Player *player, vector<int> &counts, vector<int> &pairs) {
        counts.assign(2, 0);
        pairs.assign(2, 0);
        bool is_straight = true;
        int index = 0;
        bool is_pair = false;
        for (int i = 1; i < 5; ++i) {
            if (1 != player->value[i] - player->value[i - 1]) {
                is_straight = false;
            }

            if (player->value[i] == player->value[i - 1]) {
                ++counts[index];
                pairs[index] = player->value[i];
                is_pair = true;
            } else {
                if (is_pair) {
                    ++index;
                }
                is_pair = false;
            }
        }

        bool is_flush = (1 == (int) player->suits.size());
        if (is_straight) {
            if (is_flush) {
                player->hand = 0;
            } else {
                player->hand = 4;
            }
            player->ranks.emplace_back(player->value[4]);
            return;
        }

        if (3 == counts[0]) {
            player->hand = 1;
            player->ranks.emplace_back(pairs[0]);
            return;
        }
        if (2 == counts[0] || 2 == counts[1]) {
            if (1 == counts[0] || 1 == counts[1]) {
                player->hand = 2;
            } else {
                player->hand = 5;
            }
            if (2 == counts[0]) {
                player->ranks.emplace_back(pairs[0]);
            } else {
                player->ranks.emplace_back(pairs[1]);
            }
            return;
        }
        if (1 == counts[0]) {
            if (1 == counts[1]) {
                player->hand = 6;
                player->ranks.emplace_back(pairs[1]);
            } else {
                player->hand = 7;
            }
            player->ranks.emplace_back(pairs[0]);
            for (int i = 4; i >= 0; --i) {
                if (player->value[i] != pairs[0] && player->value[i] != pairs[1]) {
                    player->ranks.emplace_back(player->value[i]);
                }
            }
            return;
        }

        if (is_flush) {
            player->hand = 3;
        } else {
            player->hand = 8;
        }
        for (int i = 4; i >= 0; --i) {
            player->ranks.emplace_back(player->value[i]);
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

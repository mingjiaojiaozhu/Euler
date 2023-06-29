#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 1024
#define SIZE_SET 256
#define SIZE_ARRAY 64

typedef struct node {
    char value;
    struct node *next;
} Set;

typedef struct {
    int *value;
    int length;
    int capacity;
} Array;

typedef struct {
    int value[5];
    Set **suits;
    int hand;
    Array *ranks;
} Player;

static void set_cards(Player *player, char **elements, int start, int *counts, int *pairs);
static int is_winner(Player **players);
static int get_value(char value);
static void set_head(Player *player, int *counts, int *pairs);
static char **split(char *line, const char *delimiter, int length);
static void append_set(char value, Set **set);
static int get_count(Set **set);
static void append_array(int value, Array *array);
static int compare(const void *p, const void *q);

void Problem054(void) {
    char *file_name = "poker.txt";
    Player *players[2];
    for (int i = 0; i < 2; ++i) {
        players[i] = (Player *) malloc(sizeof(Player));
        players[i]->suits = (Set **) malloc(sizeof(Set *) * SIZE_SET);
        players[i]->hand = 0;
        players[i]->ranks = (Array *) malloc(sizeof(Array));
        players[i]->ranks->value = (int *) malloc(sizeof(int) * SIZE_ARRAY);
        players[i]->ranks->length = 0;
        players[i]->ranks->capacity = SIZE_ARRAY;
    }
    int counts[2];
    int pairs[2];

    FILE *handle = fopen(file_name, "r");
    char line[LENGTH];
    memset(line, 0x00, sizeof(char) * LENGTH);
    int result = 0;
    while (fgets(line, LENGTH, handle)) {
        line[(int) strlen(line) - 1] = 0x00;
        char **elements = split(line, " ", 10);
        set_cards(players[0], elements, 0, counts, pairs);
        set_cards(players[1], elements, 5, counts, pairs);
        if (is_winner(players)) {
            ++result;
        }
        memset(line, 0x00, sizeof(char) * LENGTH);
    }
    fclose(handle);
    printf("%d\n", result);
}

static void set_cards(Player *player, char **elements, int start, int *counts, int *pairs) {
    for (int i = 0; i < SIZE_SET; ++i) {
        player->suits[i] = NULL;
    }
    player->ranks->length = 0;

    for (int i = 0; i < 5; ++i) {
        char *value = elements[start + i];
        player->value[i] = get_value(value[0]);
        append_set(value[1], player->suits);
    }
    qsort(player->value, 5, sizeof(int), compare);
    set_head(player, counts, pairs);
}

static int is_winner(Player **players) {
    if (players[0]->hand != players[1]->hand) {
        return (players[0]->hand < players[1]->hand) ? 1 : 0;
    }

    int length = players[0]->ranks->length;
    for (int i = 0; i < length; ++i) {
        if (players[0]->ranks->value[i] != players[1]->ranks->value[i]) {
            return (players[0]->ranks->value[i] > players[1]->ranks->value[i]) ? 1 : 0;
        }
    }
    return 1;
}

static int get_value(char value) {
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

static void set_head(Player *player, int *counts, int *pairs) {
    for (int i = 0; i < 2; ++i) {
        counts[i] = 0;
        pairs[i] = 0;
    }
    int is_straight = 1;
    int index = 0;
    int is_pair = 0;
    for (int i = 1; i < 5; ++i) {
        if (1 != player->value[i] - player->value[i - 1]) {
            is_straight = 0;
        }

        if (player->value[i] == player->value[i - 1]) {
            ++counts[index];
            pairs[index] = player->value[i];
            is_pair = 1;
        } else {
            if (is_pair) {
                ++index;
            }
            is_pair = 0;
        }
    }

    int is_flush = (1 == get_count(player->suits)) ? 1 : 0;
    if (is_straight) {
        if (is_flush) {
            player->hand = 0;
        } else {
            player->hand = 4;
        }
        append_array(player->value[4], player->ranks);
        return;
    }

    if (3 == counts[0]) {
        player->hand = 1;
        append_array(pairs[0], player->ranks);
        return;
    }
    if (2 == counts[0] || 2 == counts[1]) {
        if (1 == counts[0] || 1 == counts[1]) {
            player->hand = 2;
        } else {
            player->hand = 5;
        }
        if (2 == counts[0]) {
            append_array(pairs[0], player->ranks);
        } else {
            append_array(pairs[1], player->ranks);
        }
        return;
    }
    if (1 == counts[0]) {
        if (1 == counts[1]) {
            player->hand = 6;
            append_array(pairs[1], player->ranks);
        } else {
            player->hand = 7;
        }
        append_array(pairs[0], player->ranks);
        for (int i = 4; i >= 0; --i) {
            if (player->value[i] != pairs[0] && player->value[i] != pairs[1]) {
                append_array(player->value[i], player->ranks);
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
        append_array(player->value[i], player->ranks);
    }
}

static char **split(char *line, const char *delimiter, int length) {
    char **elements = (char **) malloc(sizeof(char *) * length);
    int index = 0;
    for (char *current = strtok(line, delimiter); current; current = strtok(NULL, delimiter)) {
        elements[index] = current;
        ++index;
    }
    return elements;
}

static void append_set(char value, Set **set) {
    int index = value % SIZE_SET;
    if (!set[index]) {
        set[index] = (Set *) malloc(sizeof(Set));
        set[index]->value = value;
        set[index]->next = NULL;
        return;
    }

    Set *current = set[index];
    if (current->value == value) {
        return;
    }

    while (current->next) {
        current = current->next;
        if (current->value == value) {
            return;
        }
    }
    current->next = (Set *) malloc(sizeof(Set));
    current->next->value = value;
    current->next->next = NULL;
}

static int get_count(Set **set) {
    int count = 0;
    for (int i = 0; i < SIZE_SET; ++i) {
        Set *current = set[i];
        while (current) {
            ++count;
            current = current->next;
        }
    }
    return count;
}

static void append_array(int value, Array *array) {
    if (array->length >= array->capacity) {
        array->value = (int *) realloc(array->value, sizeof(int) * (array->capacity + SIZE_ARRAY));
        array->capacity += SIZE_ARRAY;
    }

    array->value[array->length] = value;
    ++array->length;
}

static int compare(const void *p, const void *q) {
    return *(int *) p - *(int *) q;
}

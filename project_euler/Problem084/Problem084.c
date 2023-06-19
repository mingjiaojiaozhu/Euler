#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    int index;
    double value;
} Square;

static void set_dice(double **dice, int length, int target);
static void set_card(double **card, int length);
static void set_probability(double *probability, double **dice, double **card, int length);
static void set_squares(Square **squares, double *probability, int length, int size);
static void set_jail(double **card, int index);
static void set_community_chest(double **card, int index);
static void set_chance(double **card, int index);
static void adjust(Square **squares);

void Problem084(void) {
    int target = 4;
    int length = 40;
    double **dice = (double **) malloc(sizeof(double *) * length);
    for (int i = 0; i < length; ++i) {
        dice[i] = (double *) malloc(sizeof(double) * length);
        for (int j = 0; j < length; ++j) {
            dice[i][j] = 0;
        }
    }
    set_dice(dice, length, target);

    double **card = (double **) malloc(sizeof(double *) * length);
    for (int i = 0; i < length; ++i) {
        card[i] = (double *) malloc(sizeof(double) * length);
        for (int j = 0; j < length; ++j) {
            card[i][j] = 0;
        }
    }
    set_card(card, length);

    double *probability = (double *) malloc(sizeof(double) * length);
    set_probability(probability, dice, card, length);

    int size = 3;
    Square **squares = (Square **) malloc(sizeof(Square *) * size);
    set_squares(squares, probability, length, size);

    int result;
    if (squares[1]->value > squares[2]->value) {
        result = squares[1]->index * 100 + squares[2]->index;
    } else {
        result = squares[2]->index * 100 + squares[1]->index;
    }
    result = result * 100 + squares[0]->index;
    printf("%d\n", result);
}

static void set_dice(double **dice, int length, int target) {
    int border = (target << 1) - 1;
    double *chances = (double *) malloc(sizeof(double) * border);

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
        memcpy(dice[i] + i + 2, chances, sizeof(double) * border);
    }
    for (int i = length - border - 1; i < length - 2; ++i) {
        memcpy(dice[i] + i + 2, chances, sizeof(double) * (length - i - 2));
        memcpy(dice[i], chances + length - i - 2, sizeof(double) * (border + i - length + 2));
    }
    for (int i = length - 2; i < length; ++i) {
        memcpy(dice[i] + i - length + 2, chances, sizeof(double) * border);
    }
}

static void set_card(double **card, int length) {
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

static void set_probability(double *probability, double **dice, double **card, int length) {
    double **board = (double **) malloc(sizeof(double *) * length);
    for (int i = 0; i < length; ++i) {
        board[i] = (double *) malloc(sizeof(double) * length);
        for (int j = 0; j < length; ++j) {
            board[i][j] = 0;
        }
    }
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            for (int k = 0; k < length; ++k) {
                board[i][j] += dice[i][k] * card[k][j];
            }
        }
    }

    double *auxiliary = (double *) malloc(sizeof(double) * length);
    memcpy(auxiliary, board[0], sizeof(double) * length);
    while (1) {
        for (int i = 0; i < length; ++i) {
            probability[i] = 0;
        }
        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < length; ++j) {
                probability[i] += auxiliary[j] * board[j][i];
            }
        }

        int isSame = 1;
        for (int i = 0; i < length; ++i) {
            if (fabs(probability[i] - auxiliary[i]) > 0.00001) {
                isSame = 0;
                break;
            }
        }
        if (isSame) {
            return;
        }
        memcpy(auxiliary, probability, sizeof(double) * length);
    }
}

static void set_squares(Square **squares, double *probability, int length, int size) {
    for (int i = 0; i < size; ++i) {
        squares[i] = (Square *) malloc(sizeof(Square));
        squares[i]->index = i;
        squares[i]->value = probability[i];
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

static void set_jail(double **card, int index) {
    card[index][10] = 1;
    card[index][index] = 0;
}

static void set_community_chest(double **card, int index) {
    double chance = (double) 1 / 16;
    card[index][0] = chance;
    card[index][10] = chance;
    card[index][index] -= chance * 2;
}

static void set_chance(double **card, int index) {
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

static void adjust(Square **squares) {
    int pivot = 1;
    if (squares[1]->value > squares[2]->value) {
        pivot = 2;
    }

    if (squares[0]->value > squares[pivot]->value) {
        Square *auxiliary = squares[0];
        squares[0] = squares[pivot];
        squares[pivot] = auxiliary;
    }
}

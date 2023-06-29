#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LENGTH 1024
#define SIZE_ARRAY 64
#define SIZE_SET 256

typedef struct {
    char **value;
    int length;
    int capacity;
} Array;

typedef struct {
    char ***value;
    int length;
    int capacity;
} Array_list;

typedef struct node {
    long long value;
    struct node *next;
} Set;

static int get_word_pair(char *file_name, Array_list *word_pairs);
static void get_squares(Set ***squares, int length);
static int set_digits(char *word, long long value, int *letters, char *digits, int length);
static long long get_digits(char *word, int *letters);
static void get_letters(char *word, int *letters);
static int check_letters(int *letters);
static long long maximum(long long i, long long j);
static void append_array(char *value, Array *array);
static void append_array_list(char *value, char *pivot, Array_list *array);
static void append_set(long long value, Set **set);
static int contains(int value, Set **set);

void Problem098(void) {
    char *file_name = "words.txt";
    Array_list *word_pairs = (Array_list *) malloc(sizeof(Array_list));
    word_pairs->value = (char ***) malloc(sizeof(char **) * SIZE_ARRAY);
    word_pairs->length = 0;
    word_pairs->capacity = SIZE_ARRAY;
    int length = get_word_pair(file_name, word_pairs);

    Set ***squares = (Set ***) malloc(sizeof(Set **) * (length - 2));
    for (int i = length - 3; i >= 0; --i) {
        squares[i] = (Set **) malloc(sizeof(Set *) * SIZE_SET);
        for (int j = 0; j < SIZE_SET; ++j) {
            squares[i][j] = NULL;
        }
    }
    get_squares(squares, length);

    long long result = 0L;
    int letters[26];
    char digits[10];
    for (int i = 0; i < word_pairs->length; ++i) {
        char **words = word_pairs->value[i];
        int size = (int) strlen(words[0]);
        Set **auxiliary = squares[size - 3];
        for (int j = 0; j < SIZE_SET; ++j) {
            Set *current = auxiliary[j];
            while (current) {
                long long pivot = current->value;
                if (set_digits(words[0], pivot, letters, digits, size)) {
                    long long value = get_digits(words[1], letters);
                    if (contains(value, auxiliary) && (result < value || result < pivot)) {
                        result = maximum(value, pivot);
                    }
                }
                current = current->next;
            }
        }
    }
    printf("%lld\n", result);
}

static int get_word_pair(char *file_name, Array_list *word_pairs) {
    Array *auxiliary = (Array *) malloc(sizeof(Array));
    auxiliary->value = (char **) malloc(sizeof(char *) * SIZE_ARRAY);
    auxiliary->length = 0;
    auxiliary->capacity = SIZE_ARRAY;

    FILE *handle = fopen(file_name, "r");
    char line[LENGTH];
    memset(line, 0x00, sizeof(char) * LENGTH);
    while (fgets(line, LENGTH, handle)) {
        line[(int) strlen(line) - 1] = 0x00;
        if ((int) strlen(line) > 2) {
            append_array(line, auxiliary);
        }
        memset(line, 0x00, sizeof(char) * LENGTH);
    }
    fclose(handle);

    int letters[2][26];
    int result = 0;
    for (int i = 0; i < auxiliary->length; ++i) {
        char *pivot = auxiliary->value[i];
        get_letters(pivot, letters[0]);
        int length = (int) strlen(pivot);
        int is_pair = 0;
        for (int j = 0; j < i; ++j) {
            char *word = auxiliary->value[j];
            if (length == (int) strlen(word)) {
                get_letters(word, letters[1]);
                if (check_letters((int *) letters)) {
                    append_array_list(word, pivot, word_pairs);
                    is_pair = 1;
                }
            }
        }
        if (is_pair && result < length) {
            result = length;
        }
    }
    return result;
}

static void get_squares(Set ***squares, int length) {
    long long border = (long long) pow(10, length);
    int size = 2;
    long long index = 10L;
    while (1) {
        long long value = index * index;
        if (value >= border) {
            break;
        }

        if (size != (int) log10(value)) {
            ++size;
        }
        append_set(value, squares[size - 2]);
        ++index;
    }
}

static int set_digits(char *word, long long value, int *letters, char *digits, int length) {
    for (int i = 0; i < 26; ++i) {
        letters[i] = -1;
    }
    for (int i = 0; i < 10; ++i) {
        digits[i] = ' ';
    }

    for (int i = length - 1; i >= 0; --i) {
        char letter = word[i];
        int index = letter - 'A';
        int remainder = (int) (value % 10);
        if ((-1 != letters[index] && remainder != letters[index]) || (' ' != digits[remainder] && index != digits[remainder])) {
            return 0;
        }
        letters[index] = remainder;
        digits[remainder] = letter;
        value /= 10;
    }
    return 1;
}

static long long get_digits(char *word, int *letters) {
    long long result = 0L;
    for (char *p = word; *p; ++p) {
        result = result * 10 + letters[*p - 'A'];
    }
    return result;
}

static void get_letters(char *word, int *letters) {
    for (int i = 0; i < 26; ++i) {
        letters[i] = 0;
    }
    for (char *p = word; *p; ++p) {
        ++letters[*p - 'A'];
    }
}

static int check_letters(int *letters) {
    for (int i = 0; i < 26; ++i) {
        if (letters[i] != letters[i + 26]) {
            return 0;
        }
    }
    return 1;
}

static long long maximum(long long i, long long j) {
    return (i > j) ? i : j;
}

static void append_array(char *value, Array *array) {
    if (array->length >= array->capacity) {
        array->value = (char **) realloc(array->value, sizeof(char *) * (array->capacity + SIZE_ARRAY));
        array->capacity += SIZE_ARRAY;
    }

    array->value[array->length] = (char *) malloc(sizeof(char) * LENGTH);
    memcpy(array->value[array->length], value, (int) strlen(value));
    ++array->length;
}

static void append_array_list(char *value, char *pivot, Array_list *array) {
    if (array->length >= array->capacity) {
        array->value = (char ***) realloc(array->value, sizeof(char **) * (array->capacity + SIZE_ARRAY));
        array->capacity += SIZE_ARRAY;
    }

    array->value[array->length] = (char **) malloc(sizeof(char *) * 2);
    for (int i = 0; i < 2; ++i) {
        array->value[array->length][i] = (char *) malloc(sizeof(char) * LENGTH);
    }
    memcpy(array->value[array->length][0], value, (int) strlen(value));
    memcpy(array->value[array->length][1], pivot, (int) strlen(pivot));
    ++array->length;
}

static void append_set(long long value, Set **set) {
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

static int contains(int value, Set **set) {
    Set *current = set[value % SIZE_SET];
    while (current) {
        if (current->value == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

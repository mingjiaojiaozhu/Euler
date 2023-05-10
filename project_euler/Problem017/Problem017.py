class Problem017:
    def solution(self) -> None:
        letters_below_10 = [3, 3, 5, 4, 4, 3, 5, 5, 4]
        letters_10_to_19 = [3, 6, 6, 8, 8, 7, 7, 9, 8, 8]
        letters_whole_ten = [6, 6, 5, 5, 5, 7, 6, 6]
        letter_100, letter_and, letter_1000 = 7, 3, 8

        count_below_10 = 0
        for letter in letters_below_10:
            count_below_10 += letter

        count_below_100 = count_below_10 * 9
        for letter in letters_10_to_19:
            count_below_100 += letter
        for letter in letters_whole_ten:
            count_below_100 += letter * 10

        result = count_below_100 * 10 + count_below_10 * 100 + letter_100 * 100 * 9 + letter_and * 99 * 9 + letters_below_10[0] + letter_1000
        print(result)

import math
from typing import List

class Problem098:
    def solution(self) -> None:
        file_name, word_pairs = 'words.txt', []
        length = self.__get_word_pair(file_name, word_pairs)

        squares = [set() for _ in range(length - 2)]
        self.__get_squares(squares, length)

        result, letters, digits = 0, [0 for _ in range(26)], [' ' for _ in range(10)]
        for words in word_pairs:
            size = len(words[0])
            auxiliary = squares[size - 3]
            for pivot in auxiliary:
                if self.__set_digits(words[0], pivot, letters, digits):
                    value = self.__get_digits(words[1], letters)
                    if value in auxiliary and (result < value or result < pivot):
                        result = max(value, pivot)
        print(result)

    def __get_word_pair(self, file_name: str, word_pairs: List[List[str]]) -> int:
        auxiliary = []
        with open(file_name, 'r') as handle:
            for line in handle:
                line = line.strip()
                if len(line) > 2:
                    auxiliary.append(line)

        letters, result = [[0 for _ in range(26)] for _ in range(2)], 0
        for i, pivot in enumerate(auxiliary):
            self.__get_letters(pivot, letters[0])
            length, is_pair = len(pivot), False
            for j in range(i):
                word = auxiliary[j]
                if length == len(word):
                    self.__get_letters(word, letters[1])
                    if self.__check_letters(letters):
                        word_pairs.append([word, pivot])
                        is_pair = True

            if is_pair and result < length:
                result = length
        return result

    def __get_squares(self, squares: List[set[int]], length: int) -> None:
        border, size, index = 10 ** length, 2, 10
        while True:
            value = index * index
            if value >= border:
                break

            if size != int(math.log10(value)):
                size += 1
            squares[size - 2].add(value)
            index += 1

    def __set_digits(self, word: str, value: int, letters: List[int], digits: List[str]) -> bool:
        letters[:], digits[:] = [-1 for _ in range(26)], [' ' for _ in range(10)]
        for letter in word[::-1]:
            index, remainder = ord(letter) - ord('A'), value % 10
            if (-1 != letters[index] and remainder != letters[index]) or (' ' != digits[remainder] and index != digits[remainder]):
                return False
            letters[index], digits[remainder] = remainder, letter
            value //= 10
        return True

    def __get_digits(self, word: str, letters: List[int]) -> int:
        result = 0
        for letter in word:
            result = result * 10 + letters[ord(letter) - ord('A')]
        return result

    def __get_letters(self, word: str, letters: List[int]) -> None:
        letters[:] = [0 for _ in range(26)]
        for letter in word:
            letters[ord(letter) - ord('A')] += 1

    def __check_letters(self, letters: List[List[int]]) -> bool:
        for i in range(26):
            if letters[0][i] != letters[1][i]:
                return False
        return True

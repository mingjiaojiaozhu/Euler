import math
from typing import List

class Problem036:
    def solution(self) -> None:
        target = 1000000
        border, palindromes, binary = math.ceil(math.sqrt(target)), [0 for _ in range(2)], []

        result = 0
        for i in range(1, border):
            self.__get_palindrome(i, palindromes)
            if self.__is_binary_palindrome(palindromes[0], binary):
                result += palindromes[0]
            if self.__is_binary_palindrome(palindromes[1], binary):
                result += palindromes[1]
        print(result)

    def __get_palindrome(self, value: int, palindromes: List[int]) -> None:
        palindromes[0], palindromes[1] = value // 10, value
        while value:
            palindromes[0], palindromes[1] = palindromes[0] * 10 + value % 10, palindromes[1] * 10 + value % 10
            value //= 10

    def __is_binary_palindrome(self, value: int, binary: List[bool]) -> bool:
        binary.clear()
        while value:
            binary.append(bool(value & 1))
            value >>= 1

        start, end = 0, len(binary) - 1
        while start < end:
            if binary[start] ^ binary[end]:
                return False
            start += 1
            end -= 1
        return True

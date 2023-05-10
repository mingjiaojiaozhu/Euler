import math
from typing import List

class Problem049:
    def solution(self) -> None:
        target, other, terms, digits = 3330, 1487, [0 for _ in range(2)], [False for _ in range(10)]
        for i in range(10000 - (target << 1) - 1, 1000, -2):
            if self.__is_prime(i) and i != other:
                terms[0] = i + target
                terms[1] = terms[0] + target
                if self.__is_prime(terms[0]) and self.__is_prime(terms[1]) and self.__check_digit(i, terms, digits):
                    print('%d%d%d' % (i, terms[0], terms[1]))
                    return

    def __is_prime(self, value: int) -> bool:
        if not (value & 1):
            return 2 == value

        border = int(math.sqrt(value))
        for i in range(3, border + 1, 2):
            if not value % i:
                return False
        return 1 != value

    def __check_digit(self, value: int, terms: List[int], digits: List[bool]) -> bool:
        digits[:] = [False for _ in range(10)]
        while value:
            digits[value % 10] = True
            value //= 10

        for term in terms:
            while term:
                if not digits[term % 10]:
                    return False
                term //= 10
        return True

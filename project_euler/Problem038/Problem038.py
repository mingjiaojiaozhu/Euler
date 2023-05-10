from typing import List

class Problem038:
    def solution(self) -> None:
        digits = [False for _ in range(9)]
        for i in range(9487, 9233, -1):
            digits[:] = [False for _ in range(9)]
            if self.__is_pandigital(i, digits) and self.__is_pandigital(i << 1, digits):
                print('%d%d' % (i, i << 1))
                return

    def __is_pandigital(self, value: int, digits: List[bool]) -> bool:
        while value:
            index = value % 10 - 1
            if index < 0 or digits[index]:
                 return False
            digits[index] = True
            value //= 10
        return True

import math

class Problem023:
    def solution(self) -> None:
        start, end, abundants = 24, 28123, set()
        for i in range(start >> 1, start + 1):
            if self.__is_abundant(i):
                abundants.add(i)

        result = start * (start - 1) >> 1
        for i in range(start + 1, end + 1):
            is_non_abundant = True
            for abundant in abundants:
                if i - abundant in abundants:
                    is_non_abundant = False
                    break
            if is_non_abundant:
                result += i

            if self.__is_abundant(i):
                abundants.add(i)
        print(result)

    def __is_abundant(self, value: int) -> bool:
        border, summation = int(math.sqrt(value)), 1
        for i in range(2, border):
            if not value % i:
                summation += i + value // i
        if not value % border:
            summation += border
            if value != border * border:
                summation += value // border
        return summation > value

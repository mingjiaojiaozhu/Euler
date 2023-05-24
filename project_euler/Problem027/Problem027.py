import math

class Problem027:
    def solution(self) -> None:
        target = 1000
        border = -1 * (target - 1)
        result, pivot = 0, 0
        for i in range(3, target, 2):
            if not self.__is_prime(i):
                continue

            for j in range(border, target, 2):
                count = 1
                while self.__is_prime(count * count + count * j + i):
                    count += 1
                if pivot < count:
                    pivot, result = count, i * j
        print(result)

    def __is_prime(self, value: int) -> bool:
        if value <= 0:
            return False
        if 1 != value % 6 and 5 != value % 6:
            return 2 == value or 3 == value

        border = int(math.sqrt(value))
        for i in range(5, border + 1, 6):
            if not value % i or not value % (i + 2):
                return False
        return 1 != value

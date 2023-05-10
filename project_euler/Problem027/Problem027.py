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
        if not (value & 1):
            return 2 == value

        border = int(math.sqrt(value))
        for i in range(3, border + 1, 2):
            if not value % i:
                return False
        return 1 != value

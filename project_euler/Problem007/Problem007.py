import math

class Problem007:
    def solution(self) -> None:
        target, result, count = 10001, 1, 1
        while count < target:
            result += 2
            if self.__is_prime(result):
                count += 1
        print(result)

    def __is_prime(self, value: int) -> bool:
        if not (value & 1):
            return 2 == value

        border = int(math.sqrt(value))
        for i in range(3, border + 1, 2):
            if not value % i:
                return False
        return 1 != value

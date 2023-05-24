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
        if 1 != value % 6 and 5 != value % 6:
            return 2 == value or 3 == value

        border = int(math.sqrt(value))
        for i in range(5, border + 1, 6):
            if not value % i or not value % (i + 2):
                return False
        return 1 != value

import math

class Problem069:
    def solution(self) -> None:
        target, index, result = 1000000, 3, 2
        while True:
            if self.__is_prime(index):
                if result * index >= target:
                    print(result)
                    return
                result *= index
            index += 2

    def __is_prime(self, value: int) -> bool:
        if 1 != value % 6 and 5 != value % 6:
            return 2 == value or 3 == value

        border = int(math.sqrt(value))
        for i in range(5, border + 1, 6):
            if not value % i or not value % (i + 2):
                return False
        return 1 != value

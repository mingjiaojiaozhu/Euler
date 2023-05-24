import math

class Problem058:
    def solution(self) -> None:
        target, index, count = 0.1, 3, 0
        while True:
            value = index * index
            for _ in range(3):
                value -= index - 1
                if self.__is_prime(value):
                    count += 1

            if count < ((index << 1) - 1) * target:
                print(index)
                return
            index += 2

    def __is_prime(self, value: int) -> bool:
        if 1 != value % 6 and 5 != value % 6:
            return 2 == value or 3 == value

        border = int(math.sqrt(value))
        for i in range(5, border + 1, 6):
            if not value % i or not value % (i + 2):
                return False
        return 1 != value

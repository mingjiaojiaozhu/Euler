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
        if not (value & 1):
            return 2 == value

        border = int(math.sqrt(value))
        for i in range(3, border + 1, 2):
            if not value % i:
                return False
        return 1 != value

import math

class Problem046:
    def solution(self) -> None:
        primes, result = {2}, 3
        while True:
            if self.__is_prime(result):
                primes.add(result)
            else:
                border, is_goldbach = int(math.sqrt((result - 1) >> 1)), False
                for i in range(1, border + 1):
                    if result - (i * i << 1) in primes:
                        is_goldbach = True
                        break
                if not is_goldbach:
                    print(result)
                    return
            result += 2

    def __is_prime(self, value: int) -> bool:
        if not (value & 1):
            return 2 == value

        border = int(math.sqrt(value))
        for i in range(3, border + 1, 2):
            if not value % i:
                return False
        return 1 != value

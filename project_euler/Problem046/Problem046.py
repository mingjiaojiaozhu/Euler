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
        if 1 != value % 6 and 5 != value % 6:
            return 2 == value or 3 == value

        border = int(math.sqrt(value))
        for i in range(5, border + 1, 6):
            if not value % i or not value % (i + 2):
                return False
        return 1 != value

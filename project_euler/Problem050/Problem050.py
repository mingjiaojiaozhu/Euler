import math

class Problem050:
    def solution(self) -> None:
        target, primes, index, summation = 1000000, [2], 3, 2
        while summation < target:
            if self.__is_prime(index):
                primes.append(index)
                summation += index
            index += 2

        length = len(primes)
        for i in range(length - 1, -1, -1):
            value = summation - primes[i]
            if self.__is_prime(value):
                print(value)
                return
            summation = value

            for j in range(i, length):
                value += primes[j] - primes[j - i]
                if self.__is_prime(value) and value < target:
                    print(value)
                    return

    def __is_prime(self, value: int) -> bool:
        if 1 != value % 6 and 5 != value % 6:
            return 2 == value or 3 == value

        border = int(math.sqrt(value))
        for i in range(5, border + 1, 6):
            if not value % i or not value % (i + 2):
                return False
        return 1 != value

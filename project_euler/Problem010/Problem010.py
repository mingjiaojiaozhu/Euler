import math

class Problem010:
    def solution(self) -> None:
        target = 2000000
        length = (target + 1) >> 1
        primes = [True for _ in range(length)]
        primes[0] = False

        border = int(math.sqrt(target))
        for i in range(3, border + 1, 2):
            if primes[i >> 1]:
                for j in range(i * i >> 1, length, i):
                    primes[j] = False

        result = 2
        for i, prime in enumerate(primes[1:]):
            if prime:
                result += ((i + 1) << 1) + 1
        print(result)

from typing import List

class Problem005:
    def solution(self) -> None:
        target = 20
        powers = [0 for _ in range(target)]
        for i in range(2, target + 1):
            self.__factorize(i, powers)

        result = 1
        for i, power in enumerate(powers):
            for _ in range(0, power):
                result *= i + 1
        print(result)

    def __factorize(self, value: int, powers: List[int]) -> None:
        power = 0
        while not (value & 1):
            value >>= 1
            power += 1
        if powers[1] < power:
            powers[1] = power

        factor = 3
        while factor <= value:
            power = 0
            while not value % factor:
                value //= factor
                power += 1
            if powers[factor - 1] < power:
                powers[factor - 1] = power
            factor += 2

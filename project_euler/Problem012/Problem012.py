class Problem012:
    def solution(self) -> None:
        target, previous, index = 500, self.__get_divisors(1), 1
        while True:
            current = self.__get_divisors(index + 1)
            value = previous * current
            if value > target:
                break

            index += 1
            previous = current
        result = index * (index + 1) >> 1
        print(result)

    def __get_divisors(self, value: int) -> int:
        result = 1
        if not (value & 1):
            power = 0
            while not (value & 1):
                value >>= 1
                power += 1
            result *= power

        factor = 3
        while factor <= value:
            power = 0
            while not value % factor:
                value //= factor
                power += 1
            result *= power + 1
            factor += 2
        return result

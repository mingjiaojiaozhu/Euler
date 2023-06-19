class Problem048:
    def solution(self) -> None:
        target, result = 1000, 0
        for i in range(target // 10 * 10 + 1, target + 1):
            result += self.__get_power(i, i)
        for i in range(target // 10 - 1, -1, -1):
            for j in range(1, 10):
                value = i * 10 + j
                result += self.__get_power(value, value)
        print(result % int(1e10))

    def __get_power(self, base: int, index: int) -> int:
        if 1 == index:
            return base

        result = self.__get_power(base, index >> 1)
        result *= result
        if index & 1:
            result *= base
        return result % int(1e10)

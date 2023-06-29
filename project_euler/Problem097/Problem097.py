class Problem097:
    def solution(self) -> None:
        target, factor = 7830457, 28433
        result = (self.__get_power(target) * factor + 1) % int(1e10)
        print(result)

    def __get_power(self, value: int) -> int:
        if value < 8:
            return 2 ** value

        result = self.__get_power(value >> 1)
        result *= result
        if value & 1:
            result <<= 1
        return result % int(1e10)

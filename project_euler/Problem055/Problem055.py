class Problem055:
    def solution(self) -> None:
        target, result = 10000, 0
        for i in range(1, target + 1):
            if self.__is_lychrel(i):
                result += 1
        print(result)

    def __is_lychrel(self, value: int) -> bool:
        value += self.__reverse_value(value)
        count = 0
        while count < 50:
            auxiliary = self.__reverse_value(value)
            if value == auxiliary:
                return False
            value += auxiliary
            count += 1
        return True

    def __reverse_value(self, value: int) -> int:
        result = 0
        while value:
            result = result * 10 + value % 10
            value //= 10
        return result

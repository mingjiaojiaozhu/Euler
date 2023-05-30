class Problem056:
    def solution(self) -> None:
        target, result = 100, 0
        for i in range(2, target):
            value = i
            for _ in range(2, target):
                value *= i
                result = self.__get_digital(value, result)
        print(result)

    def __get_digital(self, value: int, pivot: int) -> int:
        result = 0
        while value:
            result += value % 10
            value //= 10
        return max(result, pivot)

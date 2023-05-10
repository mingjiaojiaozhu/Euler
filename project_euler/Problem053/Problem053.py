class Problem053:
    def solution(self) -> None:
        target, result = 1000000, 0
        for i in range(23, 101):
            result += i + 1 - (self.__get_index(i, target) << 1)
        print(result)

    def __get_index(self, value: int, target: int) -> int:
        start, end = 0, (value + 1) >> 1
        while start <= end:
            current = start + ((end - start) >> 1)
            if self.__check_combination(value, current, target):
                start = current + 1
            else:
                end = current - 1
        return start

    def __check_combination(self, value: int, count: int, target: int) -> bool:
        result = 1
        for i in range(count):
            result = result * (value - i) // (i + 1)
            if result > target:
                return False
        return True

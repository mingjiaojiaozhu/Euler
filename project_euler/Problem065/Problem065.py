class Problem065:
    def solution(self) -> None:
        target, previous, current = 100, self.__Decimal(100, 0), self.__Decimal(100, 0)
        self.__set_value(1, previous)
        self.__set_value(2, current)
        for i in range(2, target + 1):
            factor = 1
            if not i % 3:
                factor = (i << 1) // 3
            self.__get_summation(current, factor, previous)
            self.__swap_decimal(previous, current)

        result = 0
        for value in current.value[:current.length]:
            while value:
                result += value % 10
                value //= 10
        print(result)

    def __set_value(self, value: int, decimal: '__Decimal') -> None:
        decimal.value[0], decimal.length = value, 1

    def __get_summation(self, decimal: '__Decimal', factor: int, summation: '__Decimal') -> None:
        for i in range(decimal.length):
            summation.value[i] += decimal.value[i] * factor

        for i in range(summation.length):
            if summation.value[i] >= int(1e5):
                summation.value[i + 1] += summation.value[i] // int(1e5)
                summation.value[i] %= int(1e5)
        if summation.value[summation.length]:
            summation.length += 1

    def __swap_decimal(self, previous: '__Decimal', current: '__Decimal') -> None:
        length = max(previous.length, current.length)
        for i in range(length):
            previous.value[i], current.value[i] = current.value[i], previous.value[i]
        previous.length, current.length = current.length, previous.length

    class __Decimal:
        def __init__(self, capacity: int, length: int):
            self.value, self.length = [0 for _ in range(capacity)], length

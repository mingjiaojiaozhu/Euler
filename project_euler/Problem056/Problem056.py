class Problem056:
    def solution(self) -> None:
        target = 100
        decimal, result = self.__Decimal(target, 0), 0
        for i in range(2, target):
            decimal.value[:] = [0 for _ in range(target)]
            self.__set_value(i, decimal)
            for _ in range(2, target):
                self.__get_product(i, decimal)
                result = self.__get_digital(decimal, result)
        print(result)

    def __set_value(self, value: int, decimal: '__Decimal') -> None:
        decimal.value[0], decimal.length = value, 1

    def __get_product(self, value: int, decimal: '__Decimal') -> None:
        for i in range(decimal.length):
            decimal.value[i] *= value

        for i in range(decimal.length):
            if decimal.value[i] >= int(1e5):
                decimal.value[i + 1] += decimal.value[i] // int(1e5)
                decimal.value[i] %= int(1e5)
        if decimal.value[decimal.length]:
            decimal.length += 1

    def __get_digital(self, decimal: '__Decimal', pivot: int) -> int:
        result = 0
        for value in decimal.value[:decimal.length]:
            while value:
                result += value % 10
                value //= 10
        return max(result, pivot)

    class __Decimal:
        def __init__(self, capacity: int, length: int):
            self.value, self.length = [0 for _ in range(capacity)], length

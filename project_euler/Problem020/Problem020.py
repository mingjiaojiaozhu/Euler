class Problem020:
    def solution(self) -> None:
        target = 100
        decimal = self.__Decimal(target, 0)
        decimal.value[0], decimal.length = target, 1

        for i in range(target - 1, 1, -1):
            self.__get_product(i, decimal)

        result = 0
        for value in decimal.value[:decimal.length]:
            while value:
                result += value % 10
                value //= 10
        print(result)

    def __get_product(self, value: int, decimal: '__Decimal') -> None:
        for i in range(decimal.length):
            decimal.value[i] *= value

        for i in range(decimal.length):
            if decimal.value[i] >= int(1e5):
                decimal.value[i + 1] += decimal.value[i] // int(1e5)
                decimal.value[i] %= int(1e5)
        if decimal.value[decimal.length]:
            decimal.length += 1

    class __Decimal:
        def __init__(self, capacity: int, length: int):
            self.value, self.length = [0 for _ in range(capacity)], length

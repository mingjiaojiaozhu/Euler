class Problem057:
    def solution(self) -> None:
        target, numerator, denominator = 1000, self.__Decimal(100, 0), self.__Decimal(100, 0)
        self.__set_value(3, numerator)
        self.__set_value(2, denominator)

        result = 0
        for _ in range(2, target):
            self.__get_summation(denominator, numerator)
            self.__get_summation(numerator, denominator)
            self.__swap_decimal(numerator, denominator)
            if numerator.length > denominator.length or self.__get_digits(numerator.value[numerator.length - 1]) > self.__get_digits(denominator.value[denominator.length - 1]):
                result += 1
        print(result)

    def __set_value(self, value: int, decimal: '__Decimal') -> None:
        decimal.value[0], decimal.length = value, 1

    def __get_summation(self, decimal: '__Decimal', summation: '__Decimal') -> None:
        for i in range(decimal.length):
            summation.value[i] += decimal.value[i]

        for i in range(summation.length):
            if summation.value[i] >= int(1e5):
                summation.value[i + 1] += summation.value[i] // int(1e5)
                summation.value[i] %= int(1e5)
        if summation.value[summation.length]:
            summation.length += 1

    def __swap_decimal(self, numerator: '__Decimal', denominator: '__Decimal') -> None:
        length = max(numerator.length, denominator.length)
        for i in range(length):
            numerator.value[i], denominator.value[i] = denominator.value[i], numerator.value[i]
        numerator.length, denominator.length = denominator.length, numerator.length

    def __get_digits(self, value: int) -> int:
        result = 0
        while value:
            result += 1
            value //= 10
        return result

    class __Decimal:
        def __init__(self, capacity: int, length: int):
            self.value, self.length = [0 for _ in range(capacity)], length

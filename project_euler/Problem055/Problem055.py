class Problem055:
    def solution(self) -> None:
        target, result = 10000, 0
        for i in range(1, target + 1):
            if self.__is_lychrel(i):
                result += 1
        print(result)

    def __is_lychrel(self, value: int) -> bool:
        count = 0
        while count < 50:
            value += self.__reverse_value(value)
            if self.__is_palindrome(value):
                return False
            count += 1
        return True

    def __reverse_value(self, value: int) -> int:
        result = 0
        while value:
            result = result * 10 + value % 10
            value //= 10
        return result

    def __is_palindrome(self, value: int) -> bool:
        divisor = 1
        while 10 <= value // divisor:
            divisor *= 10

        while value > 1:
            head, tail = value // divisor, value % 10
            if head != tail:
                return False

            value = value % divisor // 10
            divisor //= 100
        return True

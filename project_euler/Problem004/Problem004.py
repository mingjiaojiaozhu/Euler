class Problem004:
    def solution(self) -> None:
        target, result = 100, 0
        for i in range(999, target - 1, -1):
            for j in range(i, target - 1, -1):
                value = i * j
                if self.__is_palindrome(value) and result < value:
                    result, target = value, j
                    break
        print(result)

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

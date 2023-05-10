class Problem033:
    def solution(self) -> None:
        numerator, denominator = 1, 1
        for i in range(1, 10):
            for j in range(i + 1, 10):
                if not (9 * i * j) % (10 * i - j) and (9 * i * j) // (10 * i - j) < 10:
                    numerator *= i
                    denominator *= j
        print(denominator // self.__common_divisor(denominator, numerator))

    def __common_divisor(self, i: int, j: int) -> int:
        while i % j:
            i, j = j, i % j
        return j

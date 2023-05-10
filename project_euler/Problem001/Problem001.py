class Problem001:
    def solution(self) -> None:
        target = 1000
        result = self.__get_summation(target, 3) + self.__get_summation(target, 5) - self.__get_summation(target, 3 * 5)
        print(result)

    def __get_summation(self, border: int, factor: int) -> int:
        count = (border - 1) // factor
        return factor * count * (count + 1) >> 1

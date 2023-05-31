class Problem072:
    def solution(self) -> None:
        target, fractions = 1000000, {1: self.__get_summation(1)}
        result = self.__get_fractions(target, fractions) - fractions[1]
        print(result)

    def __get_fractions(self, target: int, fractions: dict[int, int]) -> int:
        if target in fractions:
            return fractions[target]

        index, result = 2, 0
        while index <= target:
            step = target // (target // index)
            result += (step - index + 1) * self.__get_fractions(target // step, fractions)
            index = step + 1
        result = self.__get_summation(target) - result
        fractions[target] = result
        return result

    def __get_summation(self, value: int) -> int:
        return value * (value + 1) >> 1

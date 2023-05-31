class Problem073:
    def solution(self) -> None:
        target, fractions = 12000, {1: self.__get_count(1)}
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
        result = self.__get_count(target) - result
        fractions[target] = result
        return result

    def __get_count(self, value: int) -> int:
        quotient, remainder = divmod(value, 6)
        if 5 == remainder:
            return quotient * (quotient * 3 - 2 + remainder) + 1
        return quotient * (quotient * 3 - 2 + remainder)

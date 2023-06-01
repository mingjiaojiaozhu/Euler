import math

class Problem062:
    def solution(self) -> None:
        target, cubes, index, pivot = 5, {}, 5, 0
        while True:
            value = index ** 3
            digits, count = self.__get_digits(value), int(math.log10(value))
            if pivot != count:
                cubes.clear()
                pivot = count
            else:
                if digits in cubes and len(cubes[digits]) == target - 1:
                    print(cubes[digits][0])
                    return
            if digits not in cubes:
                cubes[digits] = []
            cubes[digits].append(value)
            index += 1

    def __get_digits(self, value: int) -> int:
        result = 0
        while value:
            result += int(math.pow(10, value % 10))
            value //= 10
        return result

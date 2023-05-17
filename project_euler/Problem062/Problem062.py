import math

class Problem062:
    def solution(self) -> None:
        target, cubes, index, pivot = 5, {}, 5, 0
        while True:
            value = int(math.pow(index, 3))
            summation, digit = self.__get_summation(value), int(math.log10(value))
            if pivot != digit:
                cubes.clear()
                pivot = digit
            else:
                if summation in cubes and len(cubes[summation]) == target - 1:
                    print(cubes[summation][0])
                    return
            if summation not in cubes:
                cubes[summation] = []
            cubes[summation].append(value)
            index += 1

    def __get_summation(self, value: int) -> int:
        result = 0
        while value:
            result += int(math.pow(10, value % 10))
            value //= 10
        return result

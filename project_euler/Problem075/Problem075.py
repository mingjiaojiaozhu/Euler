import math

class Problem075:
    def solution(self) -> None:
        target = 1500000
        border, perimeters = int(math.sqrt(target >> 1)), {}
        for i in range(2, border + 1):
            for j in range(1, i):
                if ((i + j) & 1) and self.__is_relatively_prime(i, j):
                    pivot = i * (i + j) << 1
                    length = pivot
                    while length < target:
                        if length in perimeters:
                            perimeters[length] += 1
                        else:
                            perimeters[length] = 1
                        length += pivot

        result = 0
        for _, value in perimeters.items():
            if 1 == value:
                result += 1
        print(result)

    def __is_relatively_prime(self, i: int, j: int) -> bool:
        while i % j:
            i, j = j, i % j
        return 1 == j

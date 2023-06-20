import math

class Problem044:
    def solution(self) -> None:
        pentagons, index = [], 1
        while True:
            current = index * (3 * index - 1) >> 1
            for pentagon in pentagons:
                if self.__is_pentagon(current + pentagon) and self.__is_pentagon(current - pentagon):
                    print(current - pentagon)
                    return
            pentagons.append(current)
            index += 1

    def __is_pentagon(self, value: int) -> bool:
        auxiliary = math.sqrt(value * 24 + 1)
        return abs(math.floor(auxiliary + 0.5) - auxiliary) < 0.00000001 and not (int(auxiliary) + 1) % 6

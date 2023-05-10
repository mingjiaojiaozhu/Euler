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
        delta = value * 24 + 1
        return math.fabs(math.floor(math.sqrt(delta) + 0.5) - math.sqrt(delta)) < 0.00000001 and not (int(math.sqrt(delta)) + 1) % 6

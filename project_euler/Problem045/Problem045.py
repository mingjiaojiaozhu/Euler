import math

class Problem045:
    def solution(self) -> None:
        index = 144
        while True:
            hexagon = index * ((index << 1) - 1)
            if self.__is_pentagon(index * ((index << 1) - 1)):
                print(hexagon)
                return
            index += 1

    def __is_pentagon(self, value: int) -> bool:
        delta = value * 24 + 1
        return abs(math.floor(math.sqrt(delta) + 0.5) - math.sqrt(delta)) < 0.00000001 and not (int(math.sqrt(delta)) + 1) % 6

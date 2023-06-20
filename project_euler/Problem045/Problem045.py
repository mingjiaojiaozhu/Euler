import math

class Problem045:
    def solution(self) -> None:
        index = 144
        while True:
            hexagon = index * ((index << 1) - 1)
            if self.__is_pentagon(hexagon):
                print(hexagon)
                return
            index += 1

    def __is_pentagon(self, value: int) -> bool:
        auxiliary = math.sqrt(value * 24 + 1)
        return abs(math.floor(auxiliary + 0.5) - auxiliary) < 0.00000001 and not (int(auxiliary) + 1) % 6

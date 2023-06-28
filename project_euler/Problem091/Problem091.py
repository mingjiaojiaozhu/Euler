class Problem091:
    def solution(self) -> None:
        target = 50
        result = target * target * 3
        for i in range(1, target):
            for j in range(1, target + 1):
                divisor = self.__common_divisor(i, j)
                result += min((target - i) * divisor // j, j * divisor // i) << 1
        print(result)

    def __common_divisor(self, i: int, j: int) -> int:
        while i % j:
            i, j = j, i % j
        return j

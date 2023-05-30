import math

class Problem057:
    def solution(self) -> None:
        target, numerator, denominator, result = 1000, 3, 2, 0
        for _ in range(2, target):
            numerator, denominator = numerator + (denominator << 1), numerator + denominator
            if int(math.log10(numerator)) > int(math.log10(denominator)):
                result += 1
        print(result)

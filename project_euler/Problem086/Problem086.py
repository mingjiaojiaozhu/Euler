import math

class Problem086:
    def solution(self) -> None:
        target, count, result = 1000000, 0, 1
        while count < target:
            result += 1
            for i in range(2, result):
                root = math.sqrt(result * result + i * i)
                if abs(math.floor(root + 0.5) - root) < 0.00000001:
                    count += i >> 1
            for i in range((result << 1) - 1, result - 1, -1):
                root = math.sqrt(result * result + i * i)
                if abs(math.floor(root + 0.5) - root) < 0.00000001:
                    count += result - ((i + 1) >> 1) + 1
        print(result)

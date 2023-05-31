class Problem076:
    def solution(self) -> None:
        target = 100
        ways = [0 for _ in range(target + 1)]
        ways[0] = 1
        for i in range(1, target):
            for j in range(i, target + 1):
                ways[j] += ways[j - i]
        print(ways[target])

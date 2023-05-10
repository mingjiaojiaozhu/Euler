class Problem028:
    def solution(self) -> None:
        target = 1001
        steps = target >> 1
        result = (steps * steps * steps * 16 + steps * 26) // 3 + steps * steps * 10 + 1
        print(result)

class Problem065:
    def solution(self) -> None:
        target, previous, current = 100, 1, 2
        for i in range(2, target + 1):
            factor = 1
            if not i % 3:
                factor = (i << 1) // 3
            previous, current = current, previous + current * factor

        result = 0
        while current:
            result += current % 10
            current //= 10
        print(result)

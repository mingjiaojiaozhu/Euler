class Problem002:
    def solution(self) -> None:
        target, previous = 4000000, [2, 8]
        result = previous[0] + previous[1]
        while True:
            current = previous[0] + (previous[1] << 2)
            if current > target:
                break

            result += current
            previous[0], previous[1] = previous[1], current
        print(result)

class Problem068:
    def solution(self) -> None:
        target = 10
        border = target >> 1
        start = border + 1
        summation = ((target * (target + 1) >> 1) + (border * (border + 1) >> 1)) // border
        pivot = summation - border - start

        ring = [start, border, pivot]
        for i in range(target, start, -1):
            ring.append(i)
            ring.append(pivot)
            pivot = summation - pivot - i
            ring.append(pivot)

        result = 0
        for value in ring:
            if value >= 10:
                result = result * 100 + value
            else:
                result = result * 10 + value
        print(result)

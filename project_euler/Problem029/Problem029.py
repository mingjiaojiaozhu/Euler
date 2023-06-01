import math

class Problem029:
    def solution(self) -> None:
        start, end, terms = 2, 100, []
        for i in range(start, end + 1):
            for j in range(start, end + 1):
                terms.append(i * math.log(j))

        terms.sort()

        result = len(terms)
        for i in range(result - 1, 0, -1):
            if abs(terms[i] - terms[i - 1]) < 0.00000001:
                result -= 1
        print(result)

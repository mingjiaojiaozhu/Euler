class Problem003:
    def solution(self) -> None:
        target = 600851475143
        while not (target & 1):
            target >>= 1
        if 1 == target:
            target = 2

        factor = 3
        while factor < target:
            while not target % factor and target != factor:
                target //= factor
            factor += 2
        print(target)

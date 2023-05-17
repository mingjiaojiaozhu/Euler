from typing import List

class Problem048:
    def solution(self) -> None:
        target, product, auxiliary, result = 1000, [0 for _ in range(2)], [0 for _ in range(2)], 0
        for i in range(target // 10 * 10 + 1, target + 1):
            self.__get_power(i, i, product, auxiliary)
            result += product[1] * int(1e5) + product[0]
        for i in range(target // 10 - 1, -1, -1):
            for j in range(1, 10):
                value = i * 10 + j
                self.__get_power(value, value, product, auxiliary)
                result += product[1] * int(1e5) + product[0]
        print(result % int(1e10))

    def __get_power(self, base: int, index: int, product: List[int], auxiliary: List[int]) -> None:
        if 1 == index:
            product[0], product[1] = base, 0
            return

        self.__get_power(base, index >> 1, product, auxiliary)
        self.__get_square(product, auxiliary)
        if index & 1:
            self.__get_product(base, product)

    def __get_square(self, product: List[int], auxiliary: List[int]) -> None:
        auxiliary[0] = product[0] * product[0]
        auxiliary[1] = product[0] * product[1] + product[1] * product[0]
        if auxiliary[0] > int(1e5):
            auxiliary[1] += auxiliary[0] // int(1e5)
            auxiliary[0] %= int(1e5)
        auxiliary[1] %= int(1e5)
        product[:] = auxiliary[:]

    def __get_product(self, value: int, product: List[int]) -> None:
        product[0] *= value
        product[1] *= value
        if product[0] > int(1e5):
            product[1] += product[0] // int(1e5)
            product[0] %= int(1e5)
        product[1] %= int(1e5)

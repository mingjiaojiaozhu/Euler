from typing import List

class Problem032:
    def solution(self) -> None:
        digits, products = [False for _ in range(9)], set()
        for i in range(1, 10):
            for j in range(10000 // i, 1233, -1):
                self.__get_products(i, j, digits, products)

        for i in range(10, 100):
            for j in range(10000 // i, 122, -1):
                self.__get_products(i, j, digits, products)

        result = 0
        for product in products:
            result += product
        print(result)

    def __get_products(self, multiplicand: int, multiplier: int, digits: List[bool], products: set[int]):
        digits[:] = [False for _ in range(9)]
        if self.__is_pandigital(multiplicand, digits) and self.__is_pandigital(multiplier, digits):
            product = multiplicand * multiplier
            if self.__is_pandigital(product, digits):
                products.add(product)

    def __is_pandigital(self, value: int, digits: List[bool]) -> bool:
        while value:
            index = value % 10 - 1
            if index < 0 or digits[index]:
                return False
            digits[index] = True
            value //= 10
        return True

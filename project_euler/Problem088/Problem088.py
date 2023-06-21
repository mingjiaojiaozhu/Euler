import math
from typing import List

class Problem088:
    def solution(self) -> None:
        target = 12000
        length = int(math.ceil(math.log(target) / math.log(2)))
        products = [2 ** (length + 1) for _ in range(target - 1)]

        digits = [1 for _ in range(length)]
        digits[0], digits[1] = 2, 2

        pivot = target - length
        while True:
            product, summation = 1, 0
            for value in digits:
                product *= value
                summation += value
            difference = product - summation
            if difference <= pivot:
                index = difference + length - 2
                if index >= 0 and products[index] > product:
                    products[index] = product
                digits[0] += 1
            else:
                if not self.__carry(digits, length):
                    break

        result, auxiliary = 0, set()
        for value in products:
            if value not in auxiliary:
                result += value
                auxiliary.add(value)
        print(result)

    def __carry(self, digits: List[int], length: int) -> bool:
        for i in range(1, length):
            if digits[i] != digits[i - 1]:
                digits[i] += 1
                value = digits[i]
                for j in range(i):
                    digits[j] = value
                return True
        return False

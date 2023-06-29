import math
from typing import List

class Problem093:
    def solution(self) -> None:
        signs, operations = ['+', '-', '*', '/'], []
        self.__get_operations(signs, operations)

        elements, auxiliary, result, calculations = [1, 2, 3, 4, 5, 6, 7, 8, 9], [0 for _ in range(4)], self.__Arithmetic(0, 0), set()
        self.__combination(elements, 0, 4, auxiliary, 0, operations, result, calculations)
        print(result.value)

    def __get_operations(self, signs: List[str], operations: List[List[str]]) -> None:
        auxiliary = [' ' for _ in range(3)]
        self.__search(signs, 3, operations, auxiliary, 0)

    def __combination(self, elements: List[int], index: int, count: int, auxiliary: List[int], size: int, operations: List[List[str]], pivot: '__Arithmetic', calculations: set[int]) -> None:
        if count == size:
            calculations.clear()
            self.__permutation(auxiliary, 0, count, operations, calculations)
            border = 1
            while border in calculations:
                border += 1
            border -= 1
            if pivot.border < border:
                pivot.border, pivot.value = border, 0
                for value in auxiliary:
                    pivot.value = pivot.value * 10 + value
            return

        for i, value in enumerate(elements[index:]):
            auxiliary[size] = value
            size += 1
            self.__combination(elements, index + i + 1, count, auxiliary, size, operations, pivot, calculations)
            size -= 1

    def __search(self, signs: List[str], count: int, operations: List[List[str]], auxiliary: List[str], size: int) -> None:
        if count == size:
            operations.append(list(auxiliary))
            return

        for value in signs:
            auxiliary[size] = value
            size += 1
            self.__search(signs, count, operations, auxiliary, size)
            size -= 1

    def __permutation(self, elements: List[int], index: int, length: int, operations: List[List[str]], calculations: set[int]) -> None:
        if index == length:
            for operation in operations:
                self.__add_calculations(self.__calculate(operation[2], self.__calculate(operation[1], self.__calculate(operation[0], elements[0], elements[1]), elements[2]), elements[3]), calculations)
                self.__add_calculations(self.__calculate(operation[1], self.__calculate(operation[0], elements[0], elements[1]), self.__calculate(operation[2], elements[2], elements[3])), calculations)
                self.__add_calculations(self.__calculate(operation[2], self.__calculate(operation[0], elements[0], self.__calculate(operation[1], elements[1], elements[2])), elements[3]), calculations)
                self.__add_calculations(self.__calculate(operation[0], elements[0], self.__calculate(operation[2], self.__calculate(operation[1], elements[1], elements[2]), elements[3])), calculations)
                self.__add_calculations(self.__calculate(operation[0], elements[0], self.__calculate(operation[1], elements[1], self.__calculate(operation[2], elements[2], elements[3]))), calculations)
            return

        self.__permutation(elements, index + 1, length, operations, calculations)
        for i in range(index + 1, length):
            elements[index], elements[i] = elements[i], elements[index]
            self.__permutation(elements, index + 1, length, operations, calculations)
            elements[index], elements[i] = elements[i], elements[index]

    def __add_calculations(self, value: float, calculations: set[int]) -> None:
        if value > 0 and abs(math.floor(value + 0.5) - value) < 0.00000001:
            calculations.add(int(value))

    def __calculate(self, sign: str, i: float, j: float) -> float:
        if '+' == sign:
            return i + j
        if '-' == sign:
            return i - j
        if '*' == sign:
            return i * j
        if abs(j) < 0.00000001:
            return -1
        return i / j

    class __Arithmetic:
        def __init__(self, border: int, value: int) -> None:
            self.border, self.value = border, value

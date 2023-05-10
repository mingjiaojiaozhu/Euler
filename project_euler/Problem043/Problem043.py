from typing import List

class Problem043:
    def solution(self) -> None:
        elements = [0 for _ in range(10)]
        elements[5] = 5
        digits = [False for _ in range(10)]
        digits[5] = True

        start = 500
        while start % 11:
            start += 1

        result = 0
        for i in range(start, 600, 11):
            elements[6], elements[7] = (i % 100) // 10, i % 10
            if 5 != elements[6] and 5 != elements[7] and elements[6] != elements[7]:
                digits[elements[6]], digits[elements[7]] = True, True
                result += self.__check13(elements, elements[6] * 100 + elements[7] * 10, digits)
                digits[elements[6]], digits[elements[7]] = False, False
        print(result)

    def __check13(self, elements: List[int], pivot: int, digits: List[bool]) -> int:
        result = 0
        for i in range(10):
            if not digits[i] and not (pivot + i) % 13:
                elements[8], digits[i] = i, True
                result += self.__check17(elements, ((pivot + i) % 100) * 10, digits)
                digits[i] = False
        return result

    def __check17(self, elements: List[int], pivot: int, digits: List[bool]) -> int:
        result = 0
        for i in range(10):
            if not digits[i] and not (pivot + i) % 17:
                elements[9], digits[i] = i, True
                self.__fill(elements, digits)
                result += self.__permutation(elements, 0, 5)
                digits[i] = False
        return result

    def __fill(self, elements: List[int], digits: List[bool]) -> None:
        index = 4
        for i in range(len(digits) - 1, -1, -1):
            if not digits[i]:
                elements[index] = i
                index -= 1

    def __permutation(self, elements: List[int], index: int, length: int) -> int:
        if index == length:
            if not elements[0] or (elements[3] & 1) \
                    or (elements[2] + elements[3] + elements[4]) % 3 \
                    or (10 * elements[4] + elements[5] - (elements[6] << 1)) % 7:
                return 0

            result = 0
            for element in elements:
                result = result * 10 + element
            return result

        result = self.__permutation(elements, index + 1, length)
        for i in range(index + 1, length):
            elements[index], elements[i] = elements[i], elements[index]
            result += self.__permutation(elements, index + 1, length)
            elements[index], elements[i] = elements[i], elements[index]
        return result

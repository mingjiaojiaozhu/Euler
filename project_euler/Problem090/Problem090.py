from typing import List

class Problem090:
    def solution(self) -> None:
        elements, ways, auxiliary = [0, 1, 2, 3, 4, 5, 6, 7, 8, 6], [], [0 for _ in range(6)]
        self.__combination(elements, 0, 6, ways, auxiliary, 0)

        squares = []
        for i in range(1, 10):
            squares.append(self.__reverse_9_to_6(i * i))

        result, arrangements = 0, set()
        for i, _ in enumerate(ways):
            for j in range(i + 1):
                if self.__check_digits(ways, i, j, squares, arrangements):
                    result += 1
        print(result)

    def __combination(self, elements: List[int], index: int, count: int, ways: List[List[int]], auxiliary: List[int], size: int) -> None:
        if count == size:
            ways.append(list(auxiliary))
            return

        for i, value in enumerate(elements[index:]):
            auxiliary[size] = value
            size += 1
            self.__combination(elements, index + i + 1, count, ways, auxiliary, size)
            size -= 1

    def __reverse_9_to_6(self, value: int) -> int:
        if 9 == value // 10:
            value -= 30
        if 9 == value % 10:
            value -= 3
        return value

    def __check_digits(self, ways: List[List[int]], start: int, end: int, squares: List[int], arrangements: set[int]) -> bool:
        arrangements.clear()
        for pivot in ways[start]:
            for value in ways[end]:
                arrangements.add(pivot * 10 + value)
                arrangements.add(value * 10 + pivot)

        for value in squares:
            if value not in arrangements:
                return False
        return True

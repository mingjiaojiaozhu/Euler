from typing import List

class Problem079:
    def solution(self) -> None:
        file_name, length = 'keylog.txt', 10
        elements, visited = [[0 for _ in range(length)] for _ in range(length)], [True for _ in range(length)]
        with open(file_name, 'r') as handle:
            for line in handle:
                self.__create_elements(int(line.strip()), elements, visited)

        digits = []
        for i in range(length):
            if not visited[i]:
                self.__search(elements, i, digits, visited, length)

        result = 0
        for value in digits[::-1]:
            result = result * 10 + value
        print(result)

    def __create_elements(self, value: int, elements: List[List[int]], visited: List[bool]) -> None:
        tail = value % 10
        visited[tail] = False
        while value >= 10:
            value //= 10
            head = value % 10
            elements[head][tail] = 1
            tail = head
            visited[tail] = False

    def __search(self, elements: List[List[int]], start: int, digits: List[int], visited: List[bool], length: int) -> None:
        visited[start], element = True, elements[start]
        for i in range(length):
            if element[i] and not visited[i]:
                self.__search(elements, i, digits, visited, length)
        digits.append(start)

import math

class Problem099:
    def solution(self) -> None:
        file_name, result = 'base_exp.txt', 0
        with open(file_name, 'r') as handle:
            index, pivot = 1, 0
            for line in handle:
                elements = line.strip().split(' ')
                value = math.log(int(elements[0])) * int(elements[1])
                if pivot < value:
                    pivot, result = value, index
                index += 1
        print(result)

import math
from typing import List

class Problem074:
    def solution(self) -> None:
        target, border = 60, 1000000
        step, permutations = int(math.log10(border)), []
        for i in range(1, 10):
            permutations.append(i)
        chains, terms, factorials = set(), {}, [0 for _ in range(10)]
        factorials[0] = 1
        for i in range(1, 10):
            factorials[i] = factorials[i - 1] * i
        counts, auxiliary, result = [], [0 for _ in range(10)], 0
        for value in permutations:
            if target == self.__get_terms(value, chains, terms, factorials, counts):
                result += self.__get_permutations(value, factorials, counts)
        for i in range(1, step):
            self.__get_digits(permutations, auxiliary)
            for value in permutations:
                if target == self.__get_terms(value, chains, terms, factorials, counts):
                    result += self.__get_permutations(value, factorials, counts)
        print(result)

    def __get_terms(self, value: int, chains: set[int], terms: dict[int, int], factorials: List[int], counts: List[int]) -> int:
        chains.clear()
        pivot = value
        while True:
            if value in terms:
                result = len(chains) + terms[value]
                break
            if value in chains:
                result = len(chains)
                break

            chains.add(value)
            value = self.__get_summation(value, factorials, counts)
        terms[pivot] = result
        return result

    def __get_permutations(self, value: int, factorials: List[int], counts: List[int]) -> int:
        length, exists_0 = 0, False
        counts[:] = [0 for _ in range(10)]
        while value:
            length += 1
            remainder = value % 10
            if not remainder:
                exists_0 = True
            counts[remainder] += 1
            value //= 10

        result = factorials[length]
        if exists_0:
            result = result * (length - 1) // length
        for count in counts:
            if 1 != count:
                result //= factorials[count]
        return result

    def __get_digits(self, permutations: List[int], auxiliary: List[int]) -> None:
        auxiliary.extend(permutations)
        permutations.clear()
        for value in auxiliary:
            remainder = value % 10
            for i in range(remainder + 1):
                permutations.append(value * 10 + i)
        auxiliary.clear()

    def __get_summation(self, value: int, factorials: List[int], counts: List[int]) -> int:
        result = 0
        while value:
            result += factorials[value % 10]
            value //= 10

        counts[:] = [0 for _ in range(10)]
        while result:
            counts[9 - result % 10] += 1
            result //= 10

        for i, count in enumerate(counts):
            for j in range(count):
                result = result * 10 + 9 - i
        return result

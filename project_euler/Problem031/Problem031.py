from typing import List

class Problem031:
    def solution(self) -> None:
        target, coins = 200, [1, 2, 5, 10, 20, 50, 100, 200]
        result = self.__get_ways(target, coins, len(coins) - 1)
        print(result)

    def __get_ways(self, target: int, coins: List[int], index: int) -> int:
        if not target or not index:
            return 1

        if target < coins[index]:
            return self.__get_ways(target, coins, index - 1)
        return self.__get_ways(target, coins, index - 1) + self.__get_ways(target - coins[index], coins, index)

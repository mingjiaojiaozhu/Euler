from typing import List

class Problem084:
    def solution(self) -> None:
        target, length = 4, 40
        dice = [[0.0 for _ in range(length)] for _ in range(length)]
        self.__set_dice(dice, length, target)

        card = [[0.0 for _ in range(length)] for _ in range(length)]
        self.__set_card(card, length)

        probability = [0.0 for _ in range(length)]
        self.__set_probability(probability, dice, card, length)

        size = 3
        squares = [self.__Square(0, 0.0) for _ in range(size)]
        self.__set_squares(squares, probability, size)

        if squares[1].value > squares[2].value:
            result = squares[1].index * 100 + squares[2].index
        else:
            result = squares[2].index * 100 + squares[1].index
        result = result * 100 + squares[0].index
        print(result)

    def __set_dice(self, dice: List[List[float]], length: int, target: int) -> None:
        border = (target << 1) - 1
        chances = [0.0 for _ in range(border)]
        start, end, count, total = 0, border - 1, 1, target * target
        while start < end:
            chance = count / total
            chances[start], chances[end] = chance, chance
            count += 1
            start += 1
            end -= 1
        chances[start] = count / total

        for i in range(length - border - 2, -1, -1):
            dice[i][i + 2:i + border + 2] = chances[:]
        for i in range(length - border - 1, length - 2):
            dice[i][i + 2:] = chances[:length - i - 2]
            dice[i][:border + i - length + 2] = chances[length - i - 2:]
        for i in range(length - 2, length):
            dice[i][i - length + 2:i + border - length + 2] = chances[:]

    def __set_card(self, card: List[List[float]], length: int) -> None:
        for i in range(length):
            card[i][i] = 1

        self.__set_jail(card, 30)
        self.__set_community_chest(card, 2)
        self.__set_community_chest(card, 17)
        self.__set_community_chest(card, 33)
        self.__set_chance(card, 7)
        self.__set_chance(card, 22)
        self.__set_chance(card, 36)

    def __set_probability(self, probability: List[float], dice: List[List[float]], card: List[List[float]], length: int) -> None:
        board = [[0.0 for _ in range(length)] for _ in range(length)]
        for i in range(length):
            for j in range(length):
                for k in range(length):
                    board[i][j] += dice[i][k] * card[k][j]

        auxiliary = list(board[0])
        while True:
            probability[:] = [0 for _ in range(length)]
            for i in range(length):
                for j in range(length):
                    probability[i] += auxiliary[j] * board[j][i]

            is_same = True
            for value, pivot in zip(probability, auxiliary):
                if abs(value - pivot) > 0.00001:
                    is_same = False
                    break
            if is_same:
                return
            auxiliary[:] = probability[:]

    def __set_squares(self, squares: List['__Square'], probability: List[float], size: int) -> None:
        for i in range(size):
            squares[i].index, squares[i].value = i, probability[i]
        self.__adjust(squares)
        for i, value in enumerate(probability[size:]):
            if squares[0].value < value:
                squares[0].index, squares[0].value = i + size, value
                self.__adjust(squares)

    def __set_jail(self, card: List[List[float]], index: int) -> None:
        card[index][10], card[index][index] = 1, 0

    def __set_community_chest(self, card: List[List[float]], index: int) -> None:
        chance = 1 / 16
        card[index][0], card[index][10] = chance, chance
        card[index][index] -= chance * 2

    def __set_chance(self, card: List[List[float]], index: int) -> None:
        chance = 1 / 16
        card[index][0], card[index][10], card[index][11], card[index][24], card[index][39], card[index][5] = chance, chance, chance, chance, chance, chance

        railway, utility = 15, 12
        if 22 == index:
            railway, utility = 25, 28
        elif 36 == index:
            railway = 5
        card[index][railway] += chance * 2
        card[index][utility] += chance
        card[index][index - 3] += chance
        card[index][index] -= chance * 10

    def __adjust(self, squares: List['__Square']) -> None:
        pivot = 1
        if squares[1].value > squares[2].value:
            pivot = 2

        if squares[0].value > squares[pivot].value:
            squares[0], squares[pivot] = squares[pivot], squares[0]

    class __Square:
        def __init__(self, index: int, value: float) -> None:
            self.index, self.value = index, value

from typing import List

class Problem054:
    def solution(self) -> None:
        file_name = 'poker.txt'
        players = [self.__Player() for _ in range(2)]
        counts, pairs = [0 for _ in range(2)], [0 for _ in range(2)]

        result = 0
        with open(file_name, 'r') as handle:
            for line in handle:
                elements = line.strip().split(' ')
                self.__set_cards(players[0], elements, 0, counts, pairs)
                self.__set_cards(players[1], elements, 5, counts, pairs)
                if self.__is_winner(players):
                    result += 1
        print(result)

    def __set_cards(self, player: '__Player', elements: List[str], start: int, counts: List[int], pairs: List[int]) -> None:
        player.suits.clear()
        player.ranks.clear()

        for i in range(5):
            value = elements[start + i]
            player.value[i] = self.__get_value(value[0])
            player.suits.add(value[1])
        player.value.sort()
        self.__set_head(player, counts, pairs)

    def __is_winner(self, players: List['__Player']) -> bool:
        if players[0].hand != players[1].hand:
            return players[0].hand < players[1].hand

        for rank0, rank1 in zip(players[0].ranks, players[1].ranks):
            if rank0 != rank1:
                return rank0 > rank1
        return True

    def __get_value(self, value: str) -> int:
        if 'A' == value:
            return 14
        if 'K' == value:
            return 13
        if 'Q' == value:
            return 12
        if 'J' == value:
            return 11
        if 'T' == value:
            return 10
        return int(value)

    def __set_head(self, player: '__Player', counts: List[int], pairs: List[int]) -> None:
        counts[:] = [0 for _ in range(2)]
        pairs[:] = [0 for _ in range(2)]
        is_straight, index, is_pair = True, 0, False
        for i in range(1, 5):
            if 1 != player.value[i] - player.value[i - 1]:
                is_straight = False

            if player.value[i] == player.value[i - 1]:
                counts[index] += 1
                pairs[index], is_pair = player.value[i], True
            else:
                if is_pair:
                    index += 1
                is_pair = False

        is_flush = (1 == len(player.suits))
        if is_straight:
            if is_flush:
                player.hand = 0
            else:
                player.hand = 4
            player.ranks.append(player.value[4])
            return

        if 3 == counts[0]:
            player.hand = 1
            player.ranks.append(pairs[0])
            return
        if 2 == counts[0] or 2 == counts[1]:
            if 1 == counts[0] or 1 == counts[1]:
                player.hand = 2
            else:
                player.hand = 5
            if 2 == counts[0]:
                player.ranks.append(pairs[0])
            else:
                player.ranks.append(pairs[1])
            return

        if 1 == counts[0]:
            if 1 == counts[1]:
                player.hand = 6
                player.ranks.append(pairs[1])
            else:
                player.hand = 7
            player.ranks.append(pairs[0])
            for i in range(4, -1, -1):
                if player.value[i] != pairs[0] and player.value[i] != pairs[1]:
                    player.ranks.append(player.value[i])
            return

        if is_flush:
            player.hand = 3
        else:
            player.hand = 8
        for i in range(4, -1, -1):
            player.ranks.append(player.value[i])

    class __Player:
        def __init__(self) -> None:
            self.value, self.suits, self.hand, self.ranks = [0 for _ in range(5)], set(), 0, []

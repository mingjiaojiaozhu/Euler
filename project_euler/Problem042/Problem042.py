import math

class Problem042:
    def solution(self) -> None:
        file_name, result = 'words.txt', 0
        with open(file_name, 'r') as handle:
            for line in handle:
                value = 0
                for letter in line.strip():
                    value += ord(letter) - ord('A') + 1
                auxiliary = math.sqrt((value << 3) + 1)
                if abs(math.floor(auxiliary + 0.5) - auxiliary) < 0.00000001 and (int(auxiliary) & 1):
                    result += 1
        print(result)

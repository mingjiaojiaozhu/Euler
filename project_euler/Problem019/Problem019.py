class Problem019:
    def solution(self) -> None:
        start, end, days = 1900, 2000, [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
        length = len(days)

        week = 1
        for day in days:
            week += day
        if not start % 4 and (start % 100 or not start % 400):
            week += 1
        week %= 7

        result = 0
        for i in range(start + 1, end + 1):
            for j in range(length):
                if not week:
                    result += 1

                week += days[j]
                if 1 == j and (not start % 4 and (start % 100 or not start % 400)):
                    week += 1
                week %= 7
        print(result)

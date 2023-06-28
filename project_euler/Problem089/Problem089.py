class Problem089:
    def solution(self) -> None:
        file_name, result = 'roman.txt', 0
        with open(file_name, 'r') as handle:
            for line in handle:
                previous, pivot, count = ' ', ' ', 1
                for value in line:
                    if pivot == value:
                        count += 1
                    else:
                        previous, pivot, count = pivot, value, 1

                    if count >= 4:
                        if ('I' == pivot and 'V' == previous) or ('X' == pivot and 'L' == previous) or ('C' == pivot and 'D' == previous):
                            result += 3
                        elif 'M' != pivot:
                            result += 2
        print(result)

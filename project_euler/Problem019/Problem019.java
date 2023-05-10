package project_euler;

public class Problem019 {
    public void solution() {
        int start = 1900;
        int end = 2000;
        int[] days = new int[]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int length = days.length;

        int week = 1;
        for (int day : days) {
            week += day;
        }
        if (0 == start % 4 && (0 != start % 100 || 0 == start % 400)) {
            ++week;
        }
        week %= 7;

        int result = 0;
        for (int i = start + 1; i <= end; ++i) {
            for (int j = 0; j < length; ++j) {
                if (0 == week) {
                    ++result;
                }

                week += days[j];
                if (1 == j && (0 == i % 4 && (0 != i % 100 || 0 == i % 400))) {
                    ++week;
                }
                week %= 7;
            }
        }
        System.out.println(result);
    }
}

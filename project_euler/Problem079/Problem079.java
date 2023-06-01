package project_euler;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Problem079 {
    public void solution() throws IOException {
        String fileName = "keylog.txt";
        int length = 10;
        int[][] elements = new int[length][length];
        for (int i = 0; i < length; ++i) {
            Arrays.fill(elements[i], 0);
        }
        boolean[] visited = new boolean[length];
        Arrays.fill(visited, true);
        try (BufferedReader handle = new BufferedReader(new InputStreamReader(new FileInputStream(fileName)))) {
            String line;
            while (null != (line = handle.readLine())) {
                createElements(Integer.parseInt(line), elements, visited);
            }
        }

        List<Integer> digits = new ArrayList<>();
        for (int i = 0; i < length; ++i) {
            if (!visited[i]) {
                search(elements, i, digits, visited, length);
            }
        }

        int result = 0;
        for (int i = digits.size() - 1; i >= 0; --i) {
            result = result * 10 + digits.get(i);
        }
        System.out.println(result);
    }

    private void createElements(int value, int[][] elements, boolean[] visited) {
        int tail = value % 10;
        visited[tail] = false;
        while (value >= 10) {
            value /= 10;
            int head = value % 10;
            elements[head][tail] = 1;
            tail = head;
            visited[tail] = false;
        }
    }

    private void search(int[][] elements, int start, List<Integer> digits, boolean[] visited, int length) {
        visited[start] = true;
        int[] element = elements[start];
        for (int i = 0; i < length; ++i) {
            if (0 != element[i] && !visited[i]) {
                search(elements, i, digits, visited, length);
            }
        }
        digits.add(start);
    }
}

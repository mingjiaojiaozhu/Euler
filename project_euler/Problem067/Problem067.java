package project_euler;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;

public class Problem067 {
    public void solution() throws IOException {
        String fileName = "triangle.txt";
        int border = 100;
        int[][] target = new int[border][border];

        try (BufferedReader handle = new BufferedReader(new InputStreamReader(new FileInputStream(fileName)))) {
            String line;
            int index = 0;
            while (null != (line = handle.readLine())) {
                String[] elements = line.split(" ");
                for (int i = elements.length - 1; i >= 0; --i) {
                    target[index][i] = Integer.parseInt(elements[i]);
                }
                ++index;
            }
        }

        for (int i = border - 1; i > 0; --i) {
            for (int j = i - 1; j >= 0; --j) {
                target[i - 1][j] += Math.max(target[i][j], target[i][j + 1]);
            }
        }
        System.out.println(target[0][0]);
    }
}

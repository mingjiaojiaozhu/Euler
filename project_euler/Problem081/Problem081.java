package project_euler;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;

public class Problem081 {
    public void solution() throws IOException {
        String fileName = "matrix.txt";
        int border = 80;
        int[][] target = new int[border][border];
        try (BufferedReader handle = new BufferedReader(new InputStreamReader(new FileInputStream(fileName)))) {
            String line;
            int index = 0;
            while (null != (line = handle.readLine())) {
                String[] elements = line.split(" ");
                for (int i = 0; i < border; ++i) {
                    target[index][i] = Integer.parseInt(elements[i]);
                }
                ++index;
            }
        }

        for (int i = 1; i < border; ++i) {
            target[0][i] += target[0][i - 1];
            target[i][0] += target[i - 1][0];
        }
        for (int i = 1; i < border; ++i) {
            for (int j = 1; j < border; ++j) {
                target[i][j] += Math.min(target[i - 1][j], target[i][j - 1]);
            }
        }
        System.out.println(target[border - 1][border - 1]);
    }
}

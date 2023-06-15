package project_euler;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;

public class Problem082 {
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

        int[] ways = new int[border];
        for (int i = 0; i < border; ++i) {
            ways[i] = target[i][border - 1];
        }
        for (int i = border - 2; i >= 0; --i) {
            ways[0] += target[0][i];
            for (int j = 1; j < border; ++j) {
                if (ways[j] > ways[j - 1]) {
                    ways[j] = ways[j - 1] + target[j][i];
                } else {
                    ways[j] += target[j][i];
                }
            }
            for (int j = border - 2; j >= 0; --j) {
                if (ways[j] > ways[j + 1] + target[j][i]) {
                    ways[j] = ways[j + 1] + target[j][i];
                }
            }
        }

        int result = ways[0];
        for (int value : ways) {
            if (result > value) {
                result = value;
            }
        }
        System.out.println(result);
    }
}

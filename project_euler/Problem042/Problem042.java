package project_euler;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;

public class Problem042 {
    public void solution() throws IOException {
        String fileName = "words.txt";
        int result = 0;
        try (BufferedReader handle = new BufferedReader(new InputStreamReader(new FileInputStream(fileName)))) {
            String line;
            while (null != (line = handle.readLine())) {
                int value = 0;
                for (char letter : line.toCharArray()) {
                    value += letter - 'A' + 1;
                }
                int delta = (value << 3) + 1;
                if (Math.abs(Math.floor(Math.sqrt(delta) + 0.5) - Math.sqrt(delta)) < 0.00000001 && 0 != ((int) Math.sqrt(delta) & 1)) {
                    ++result;
                }
            }
        }
        System.out.println(result);
    }
}

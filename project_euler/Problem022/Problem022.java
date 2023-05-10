package project_euler;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Problem022 {
    public void solution() throws IOException {
        String fileName = "names.txt";
        List<String> names = new ArrayList<>();

        try (BufferedReader handle = new BufferedReader(new InputStreamReader(new FileInputStream(fileName)))) {
            String line;
            while (null != (line = handle.readLine())) {
                names.add(line);
            }
        }

        Collections.sort(names);

        long result = 0L;
        for (int i = names.size() - 1; i >= 0; --i) {
            int score = 0;
            for (char letter : names.get(i).toCharArray()) {
                score += letter - 'A' + 1;
            }
            result += (long) score * (i + 1);
        }
        System.out.println(result);
    }
}

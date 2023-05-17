package project_euler;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Problem059 {
    public void solution() throws IOException {
        String fileName = "cipher.txt";
        List<Integer> codes = new ArrayList<>();
        Map<Integer, Integer>[] counts = new HashMap[3];
        for (int i = 0; i < 3; ++i) {
            counts[i] = new HashMap<>();
        }

        try (BufferedReader handle = new BufferedReader(new InputStreamReader(new FileInputStream(fileName)))) {
            String line;
            int index = 0;
            while (null != (line = handle.readLine())) {
                int code = Integer.parseInt(line);
                codes.add(code);
                counts[index].put(code, counts[index].getOrDefault(code, 0) + 1);
                ++index;
                if (3 == index) {
                    index = 0;
                }
            }
        }

        int[] keys = new int[3];
        for (int i = 0; i < 3; ++i) {
            int pivot = 0;
            for (Map.Entry<Integer, Integer> entry : counts[i].entrySet()) {
                if (pivot < entry.getValue()) {
                    pivot = entry.getValue();
                    keys[i] = entry.getKey();
                }
            }
            keys[i] ^= 32;
        }

        int result = 0;
        int index = 0;
        for (int code : codes) {
            result += code ^ keys[index];
            ++index;
            if (3 == index) {
                index = 0;
            }
        }
        System.out.println(result);
    }
}

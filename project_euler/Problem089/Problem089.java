package project_euler;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;

public class Problem089 {
    public void solution() throws IOException {
        String fileName = "roman.txt";
        int result = 0;
        try (BufferedReader handle = new BufferedReader(new InputStreamReader(new FileInputStream(fileName)))) {
            String line;
            while (null != (line = handle.readLine())) {
                char previous = ' ';
                char pivot = ' ';
                int count = 1;
                for (char value : line.toCharArray()) {
                    if (pivot == value) {
                        ++count;
                    } else {
                        previous = pivot;
                        pivot = value;
                        count = 1;
                    }

                    if (count >= 4) {
                        if (('I' == pivot && 'V' == previous) || ('X' == pivot && 'L' == previous) || ('C' == pivot && 'D' == previous)) {
                            result += 3;
                        } else if ('M' != pivot) {
                            result += 2;
                        }
                    }
                }
            }
        }
        System.out.println(result);
    }
}

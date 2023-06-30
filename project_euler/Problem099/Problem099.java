package project_euler;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;

public class Problem099 {
    public void solution() throws IOException {
        String fileName = "base_exp.txt";
        int result = 0;
        try (BufferedReader handle = new BufferedReader(new InputStreamReader(new FileInputStream(fileName)))) {
            String line;
            int index = 1;
            double pivot = 0;
            while (null != (line = handle.readLine())) {
                String[] elements = line.split(" ");
                double value = Math.log(Integer.parseInt(elements[0])) * Integer.parseInt(elements[1]);
                if (pivot < value) {
                    pivot = value;
                    result = index;
                }
                ++index;
            }
        }
        System.out.println(result);
    }
}

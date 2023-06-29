package project_euler;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Problem098 {
    public void solution() throws IOException {
        String fileName = "words.txt";
        List<String[]> wordPairs = new ArrayList<>();
        int length = getWordPair(fileName, wordPairs);

        Set<Long>[] squares = new HashSet[length - 2];
        for (int i = length - 3; i >= 0; --i) {
            squares[i] = new HashSet<>();
        }
        getSquares(squares, length);

        long result = 0L;
        int[] letters = new int[26];
        char[] digits = new char[10];
        for (String[] words : wordPairs) {
            int size = words[0].length();
            Set<Long> auxiliary = squares[size - 3];
            for (long pivot : auxiliary) {
                if (setDigits(words[0], pivot, letters, digits, size)) {
                    long value = getDigits(words[1], letters);
                    if (auxiliary.contains(value) && (result < value || result < pivot)) {
                        result = Math.max(value, pivot);
                    }
                }
            }
        }
        System.out.println(result);
    }

    private int getWordPair(String fileName, List<String[]> wordPairs) throws IOException {
        List<String> auxiliary = new ArrayList<>();
        try (BufferedReader handle = new BufferedReader(new InputStreamReader(new FileInputStream(fileName)))) {
            String line;
            while (null != (line = handle.readLine())) {
                if (line.length() > 2) {
                    auxiliary.add(line);
                }
            }
        }

        int[][] letters = new int[2][26];
        int result = 0;
        for (int i = auxiliary.size() - 1; i > 0; --i) {
            String pivot = auxiliary.get(i);
            getLetters(pivot, letters[0]);
            int length = pivot.length();
            boolean isPair = false;
            for (int j = 0; j < i; ++j) {
                String word = auxiliary.get(j);
                if (length == word.length()) {
                    getLetters(word, letters[1]);
                    if (checkLetters(letters)) {
                        wordPairs.add(new String[]{word, pivot});
                        isPair = true;
                    }
                }
            }
            if (isPair && result < length) {
                result = length;
            }
        }
        return result;
    }

    private void getSquares(Set<Long>[] squares, int length) {
        long border = (long) Math.pow(10, length);
        int size = 2;
        long index = 10L;
        while (true) {
            long value = index * index;
            if (value >= border) {
                break;
            }

            if (size != (int) Math.log10(value)) {
                ++size;
            }
            squares[size - 2].add(value);
            ++index;
        }
    }

    private boolean setDigits(String word, long value, int[] letters, char[] digits, int length) {
        Arrays.fill(letters, -1);
        Arrays.fill(digits, ' ');
        for (int i = length - 1; i >= 0; --i) {
            char letter = word.charAt(i);
            int index = letter - 'A';
            int remainder = (int) (value % 10);
            if ((-1 != letters[index] && remainder != letters[index]) || (' ' != digits[remainder] && index != digits[remainder])) {
                return false;
            }
            letters[index] = remainder;
            digits[remainder] = letter;
            value /= 10;
        }
        return true;
    }

    private long getDigits(String word, int[] letters) {
        long result = 0L;
        for (char letter : word.toCharArray()) {
            result = result * 10 + letters[letter - 'A'];
        }
        return result;
    }

    private void getLetters(String word, int[] letters) {
        Arrays.fill(letters, 0);
        for (char letter : word.toCharArray()) {
            ++letters[letter - 'A'];
        }
    }

    private boolean checkLetters(int[][] letters) {
        for (int i = 0; i < 26; ++i) {
            if (letters[0][i] != letters[1][i]) {
                return false;
            }
        }
        return true;
    }
}

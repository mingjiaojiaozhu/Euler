package project_euler;

import java.util.ArrayList;
import java.util.List;

public class Problem036 {
    public void solution() {
        int target = 1000000;
        int border = (int) Math.ceil(Math.sqrt(target));
        int[] palindromes = new int[2];
        List<Boolean> binary = new ArrayList<>();

        int result = 0;
        for (int i = 1; i < border; ++i) {
            getPalindrome(i, palindromes);
            if (isBinaryPalindrome(palindromes[0], binary)) {
                result += palindromes[0];
            }
            if (isBinaryPalindrome(palindromes[1], binary)) {
                result += palindromes[1];
            }
        }
        System.out.println(result);
    }

    private void getPalindrome(int value, int[] palindromes) {
        palindromes[0] = value / 10;
        palindromes[1] = value;
        while (0 != value) {
            palindromes[0] = palindromes[0] * 10 + value % 10;
            palindromes[1] = palindromes[1] * 10 + value % 10;
            value /= 10;
        }
    }

    private boolean isBinaryPalindrome(int value, List<Boolean> binary) {
        binary.clear();
        while (0 != value) {
            binary.add(0 != (value & 1));
            value >>= 1;
        }

        int start = 0;
        int end = binary.size() - 1;
        while (start < end) {
            if (binary.get(start) ^ binary.get(end)) {
                return false;
            }
            ++start;
            --end;
        }
        return true;
    }
}

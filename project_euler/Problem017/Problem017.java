package project_euler;

public class Problem017 {
    public void solution() {
        int[] lettersBelow10 = new int[]{3, 3, 5, 4, 4, 3, 5, 5, 4};
        int[] letters10To19 = new int[]{3, 6, 6, 8, 8, 7, 7, 9, 8, 8};
        int[] lettersWholeTen = new int[]{6, 6, 5, 5, 5, 7, 6, 6};
        int letter100 = 7;
        int letterAnd = 3;
        int letter1000 = 8;

        int countBelow10 = 0;
        for (int letter : lettersBelow10) {
            countBelow10 += letter;
        }

        int countBelow100 = countBelow10 * 9;
        for (int letter : letters10To19) {
            countBelow100 += letter;
        }
        for (int letter : lettersWholeTen) {
            countBelow100 += letter * 10;
        }

        int result = countBelow100 * 10 + countBelow10 * 100 + letter100 * 100 * 9 + letterAnd * 99 * 9 + lettersBelow10[0] + letter1000;
        System.out.println(result);
    }
}

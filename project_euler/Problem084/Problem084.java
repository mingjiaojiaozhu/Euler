package project_euler;

import java.util.Arrays;

public class Problem084 {
    public void solution() {
        int target = 4;
        int length = 40;
        double[][] dice = new double[length][length];
        for (int i = 0; i < length; ++i) {
            Arrays.fill(dice[i], 0);
        }
        setDice(dice, length, target);

        double[][] card = new double[length][length];
        for (int i = 0; i < length; ++i) {
            Arrays.fill(card[i], 0);
        }
        setCard(card, length);

        double[] probability = new double[length];
        setProbability(probability, dice, card, length);

        int size = 3;
        Square[] squares = new Square[size];
        setSquares(squares, probability, length, size);

        int result;
        if (squares[1].value > squares[2].value) {
            result = squares[1].index * 100 + squares[2].index;
        } else {
            result = squares[2].index * 100 + squares[1].index;
        }
        result = result * 100 + squares[0].index;
        System.out.println(result);
    }

    private void setDice(double[][] dice, int length, int target) {
        int border = (target << 1) - 1;
        double[] chances = new double[border];

        int start = 0;
        int end = border - 1;
        int count = 1;
        int total = target * target;
        while (start < end) {
            double chance = (double) count / total;
            chances[start] = chance;
            chances[end] = chance;
            ++count;
            ++start;
            --end;
        }
        chances[start] = (double) count / total;

        for (int i = length - border - 2; i >= 0; --i) {
            System.arraycopy(chances, 0, dice[i], i + 2, border);
        }
        for (int i = length - border - 1; i < length - 2; ++i) {
            System.arraycopy(chances, 0, dice[i], i + 2, length - i - 2);
            System.arraycopy(chances, length - i - 2, dice[i], 0, border + i - length + 2);
        }
        for (int i = length - 2; i < length; ++i) {
            System.arraycopy(chances, 0, dice[i], i - length + 2, border);
        }
    }

    private void setCard(double[][] card, int length) {
        for (int i = 0; i < length; ++i) {
            card[i][i] = 1;
        }
        setJail(card, 30);
        setCommunityChest(card, 2);
        setCommunityChest(card, 17);
        setCommunityChest(card, 33);
        setChance(card, 7);
        setChance(card, 22);
        setChance(card, 36);
    }

    private void setProbability(double[] probability, double[][] dice, double[][] card, int length) {
        double[][] board = new double[length][length];
        for (int i = 0; i < length; ++i) {
            Arrays.fill(board[i], 0);
        }
        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < length; ++j) {
                for (int k = 0; k < length; ++k) {
                    board[i][j] += dice[i][k] * card[k][j];
                }
            }
        }

        double[] auxiliary = board[0].clone();
        while (true) {
            Arrays.fill(probability, 0);
            for (int i = 0; i < length; ++i) {
                for (int j = 0; j < length; ++j) {
                    probability[i] += auxiliary[j] * board[j][i];
                }
            }

            boolean isSame = true;
            for (int i = 0; i < length; ++i) {
                if (Math.abs(probability[i] - auxiliary[i]) > 0.00001) {
                    isSame = false;
                    break;
                }
            }
            if (isSame) {
                return;
            }
            System.arraycopy(probability, 0, auxiliary, 0, length);
        }
    }

    private void setSquares(Square[] squares, double[] probability, int length, int size) {
        for (int i = 0; i < size; ++i) {
            squares[i] = new Square(i, probability[i]);
        }
        adjust(squares);
        for (int i = size; i < length; ++i) {
            double value = probability[i];
            if (squares[0].value < value) {
                squares[0].index = i;
                squares[0].value = value;
                adjust(squares);
            }
        }
    }

    private void setJail(double[][] card, int index) {
        card[index][10] = 1;
        card[index][index] = 0;
    }

    private void setCommunityChest(double[][] card, int index) {
        double chance = (double) 1 / 16;
        card[index][0] = chance;
        card[index][10] = chance;
        card[index][index] -= chance * 2;
    }

    private void setChance(double[][] card, int index) {
        double chance = (double) 1 / 16;
        card[index][0] = chance;
        card[index][10] = chance;
        card[index][11] = chance;
        card[index][24] = chance;
        card[index][39] = chance;
        card[index][5] = chance;

        int railway = 15;
        int utility = 12;
        if (22 == index) {
            railway = 25;
            utility = 28;
        } else if (36 == index) {
            railway = 5;
        }
        card[index][railway] += chance * 2;
        card[index][utility] += chance;
        card[index][index - 3] += chance;
        card[index][index] -= chance * 10;
    }

    private void adjust(Square[] squares) {
        int pivot = 1;
        if (squares[1].value > squares[2].value) {
            pivot = 2;
        }

        if (squares[0].value > squares[pivot].value) {
            Square auxiliary = squares[0];
            squares[0] = squares[pivot];
            squares[pivot] = auxiliary;
        }
    }

    private static class Square {
        public int index;
        public double value;

        public Square(int index, double value) {
            this.index = index;
            this.value = value;
        }
    }
}

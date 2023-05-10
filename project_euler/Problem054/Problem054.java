package project_euler;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Objects;
import java.util.Set;

public class Problem054 {
    public void solution() throws IOException {
        String fileName = "poker.txt";
        Player[] players = new Player[2];
        for (int i = 0; i < 2; ++i) {
            players[i] = new Player();
        }
        int[] counts = new int[2];
        int[] pairs = new int[2];

        int result = 0;
        try (BufferedReader handle = new BufferedReader(new InputStreamReader(new FileInputStream(fileName)))) {
            String line;
            while (null != (line = handle.readLine())) {
                String[] elements = line.split(" ");
                setCards(players[0], elements, 0, counts, pairs);
                setCards(players[1], elements, 5, counts, pairs);
                if (isWinner(players)) {
                    ++result;
                }
            }
        }
        System.out.println(result);
    }

    private void setCards(Player player, String[] elements, int start, int[] counts, int[] pairs) {
        player.suits.clear();
        player.ranks.clear();

        for (int i = 0; i < 5; ++i) {
            String value = elements[start + i];
            player.value[i] = getValue(value.substring(0, 1));
            player.suits.add(value.substring(1, 2));
        }
        Arrays.sort(player.value);
        setHead(player, counts, pairs);
    }

    private boolean isWinner(Player[] players) {
        if (players[0].hand != players[1].hand) {
            return players[0].hand < players[1].hand;
        }

        int length = players[0].ranks.size();
        for (int i = 0; i < length; ++i) {
            if (!Objects.equals(players[0].ranks.get(i), players[1].ranks.get(i))) {
                return players[0].ranks.get(i) > players[1].ranks.get(i);
            }
        }
        return true;
    }

    private int getValue(String value) {
        if ("A".equals(value)) {
            return 14;
        }
        if ("K".equals(value)) {
            return 13;
        }
        if ("Q".equals(value)) {
            return 12;
        }
        if ("J".equals(value)) {
            return 11;
        }
        if ("T".equals(value)) {
            return 10;
        }
        return Integer.parseInt(value);
    }

    private void setHead(Player player, int[] counts, int[] pairs) {
        Arrays.fill(counts, 0);
        Arrays.fill(pairs, 0);
        boolean isStraight = true;
        int index = 0;
        boolean isPair = false;
        for (int i = 1; i < 5; ++i) {
            if (1 != player.value[i] - player.value[i - 1]) {
                isStraight = false;
            }

            if (player.value[i] == player.value[i - 1]) {
                ++counts[index];
                pairs[index] = player.value[i];
                isPair = true;
            } else {
                if (isPair) {
                    ++index;
                }
                isPair = false;
            }
        }

        boolean isFlush = (1 == player.suits.size());
        if (isStraight) {
            if (isFlush) {
                player.hand = 0;
            } else {
                player.hand = 4;
            }
            player.ranks.add(player.value[4]);
            return;
        }

        if (3 == counts[0]) {
            player.hand = 1;
            player.ranks.add(pairs[0]);
            return;
        }
        if (2 == counts[0] || 2 == counts[1]) {
            if (1 == counts[0] || 1 == counts[1]) {
                player.hand = 2;
            } else {
                player.hand = 5;
            }
            if (2 == counts[0]) {
                player.ranks.add(pairs[0]);
            } else {
                player.ranks.add(pairs[1]);
            }
            return;
        }
        if (1 == counts[0]) {
            if (1 == counts[1]) {
                player.hand = 6;
                player.ranks.add(pairs[1]);
            } else {
                player.hand = 7;
            }
            player.ranks.add(pairs[0]);
            for (int i = 4; i >= 0; --i) {
                if (player.value[i] != pairs[0] && player.value[i] != pairs[1]) {
                    player.ranks.add(player.value[i]);
                }
            }
            return;
        }

        if (isFlush) {
            player.hand = 3;
        } else {
            player.hand = 8;
        }
        for (int i = 4; i >= 0; --i) {
            player.ranks.add(player.value[i]);
        }
    }

    private static class Player {
        public int[] value;
        public Set<String> suits;
        public int hand;
        public List<Integer> ranks;

        public Player() {
            this.value = new int[5];
            this.suits = new HashSet<>();
            this.hand = 0;
            this.ranks = new ArrayList<>();
        }
    }
}

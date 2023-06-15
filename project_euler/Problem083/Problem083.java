package project_euler;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;

public class Problem083 {
    public void solution() throws IOException {
        String fileName = "matrix.txt";
        int border = 80;
        int[][] target = new int[border][border];
        try (BufferedReader handle = new BufferedReader(new InputStreamReader(new FileInputStream(fileName)))) {
            String line;
            int index = 0;
            while (null != (line = handle.readLine())) {
                String[] elements = line.split(" ");
                for (int i = elements.length - 1; i >= 0; --i) {
                    target[index][i] = Integer.parseInt(elements[i]);
                }
                ++index;
            }
        }

        int length = border * border;
        int[][] edges = new int[length][length];
        for (int i = 0; i < length; ++i) {
            Arrays.fill(edges[i], 0);
        }
        for (int i = 0; i < border; ++i) {
            for (int j = 0; j < border; ++j) {
                if (i > 0) {
                    edges[i * border + j][(i - 1) * border + j] = target[i - 1][j];
                }
                if (j > 0) {
                    edges[i * border + j][i * border + j - 1] = target[i][j - 1];
                }
                if (i < border - 1) {
                    edges[i * border + j][(i + 1) * border + j] = target[i + 1][j];
                }
                if (j < border - 1) {
                    edges[i * border + j][i * border + j + 1] = target[i][j + 1];
                }
            }
        }

        int[] ways = new int[length];
        search(edges, length, ways);
        System.out.println(ways[length - 1] + target[0][0]);
    }

    private void search(int[][] edges, int length, int[] ways) {
        boolean[] visited = new boolean[length];
        Arrays.fill(visited, false);
        Queue<Heap> queue = new PriorityQueue<>(Comparator.comparingInt(p -> p.weight));
        queue.offer(new Heap(0, 0));
        while (!queue.isEmpty()) {
            Heap node = queue.poll();
            int index = node.index;
            int weight = node.weight;
            if (visited[index]) {
                continue;
            }

            ways[index] = weight;
            visited[index] = true;
            for (int i = 0; i < length; ++i) {
                if (0 != edges[index][i] && !visited[i]) {
                    queue.offer(new Heap(i, weight + edges[index][i]));
                }
            }
        }
    }

    private static class Heap {
        public int index;
        public int weight;

        public Heap(int index, int weight) {
            this.index = index;
            this.weight = weight;
        }
    }
}

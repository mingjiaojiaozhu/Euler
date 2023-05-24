package project_euler;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Problem060 {
    public void solution() {
        int target = 5;
        List<Integer> primes = new ArrayList<>();
        for (int i = 3; i < 10000; i += 2) {
            if (isPrime(i)) {
                primes.add(i);
            }
        }

        int length = primes.size();
        int[][] edges = new int[length][length];
        for (int i = 0; i < length; ++i) {
            Arrays.fill(edges[i], 0);
        }
        for (int i = 0; i < length; ++i) {
            int pivot = primes.get(i);
            for (int j = i + 1; j < length; ++j) {
                int value = primes.get(j);
                if (isPrime(merge(pivot, value)) && isPrime(merge(value, pivot))) {
                    edges[i][j] = 1;
                    edges[j][i] = 1;
                }
            }
        }

        List<Integer> cliques = new ArrayList<>();
        List<Integer> indexes = new ArrayList<>();
        for (int i = 0; i < length; ++i) {
            indexes.add(i);
        }
        search(primes, edges, cliques, indexes, target);
    }

    private boolean isPrime(int value) {
        if (0 == (value & 1)) {
            return 2 == value;
        }

        int border = (int) Math.sqrt(value);
        for (int i = 3; i <= border; i += 2) {
            if (0 == value % i) {
                return false;
            }
        }
        return 1 != value;
    }

    private int merge(int head, int tail) {
        return head * (int) Math.pow(10, (int) Math.log10(tail) + 1) + tail;
    }

    private void search(List<Integer> primes, int[][] edges, List<Integer> cliques, List<Integer> indexes, int target) {
        if (indexes.isEmpty()) {
            if (cliques.size() == target) {
                int result = 0;
                for (int index : cliques) {
                    result += primes.get(index);
                }
                System.out.println(result);
            }
            return;
        }

        int start = indexes.get(0);
        for (int i = indexes.size() - 1; i >= 0; --i) {
            int index = indexes.get(i);
            if (0 == edges[start][index]) {
                cliques.add(index);
                search(primes, edges, cliques, getAdjacents(edges, indexes, index), target);
                cliques.remove(cliques.size() - 1);
                indexes.remove((Integer) index);
            }
        }
    }

    private List<Integer> getAdjacents(int[][] edges, List<Integer> indexes, int start) {
        List<Integer> auxiliary = new ArrayList<>();
        for (int index : indexes) {
            if (0 != edges[start][index]) {
                auxiliary.add(index);
            }
        }
        return auxiliary;
    }
}

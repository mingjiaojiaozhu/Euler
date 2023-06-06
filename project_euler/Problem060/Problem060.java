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
        for (int i = 1; i < length; ++i) {
            int value = primes.get(i);
            if (checkPrime(merge(3, value), primes) && checkPrime(merge(value, 3), primes)) {
                edges[0][i] = 1;
                edges[i][0] = 1;
            }
        }
        for (int i = 1; i < length; ++i) {
            int pivot = primes.get(i);
            for (int j = i + 1; j < length; ++j) {
                int value = primes.get(j);
                if (pivot % 3 == value % 3 && checkPrime(merge(pivot, value), primes) && checkPrime(merge(value, pivot), primes)) {
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

    private boolean checkPrime(int value, List<Integer> primes) {
        if (value < 10000) {
            int start = 0;
            int end = primes.size() - 1;
            while (start <= end) {
                int current = start + ((end - start) >> 1);
                int prime = primes.get(current);
                if (prime == value) {
                    return true;
                }

                if (prime < value) {
                    start = current + 1;
                } else {
                    end = current - 1;
                }
            }
            return false;
        }

        int border = (int) Math.sqrt(value);
        int start = 0;
        int end = primes.size() - 1;
        while (start <= end) {
            int current = start + ((end - start) >> 1);
            if (primes.get(current) <= border) {
                start = current + 1;
            } else {
                end = current - 1;
            }
        }

        for (int i = 0; i < start; ++i) {
            if (0 == value % primes.get(i)) {
                return false;
            }
        }
        return true;
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

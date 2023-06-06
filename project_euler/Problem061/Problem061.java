package project_euler;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Problem061 {
    public void solution() {
        int target = 6;
        List<Polygonal> polygonals = new ArrayList<>();
        addTriangle(polygonals);
        addSquare(polygonals);
        addPentagonal(polygonals);
        addHexagonal(polygonals);
        addHeptagonal(polygonals);
        addOctagonal(polygonals);

        int length = polygonals.size();
        int[][] edges = new int[length][length];
        for (int i = 0; i < length; ++i) {
            Arrays.fill(edges[i], 0);
        }
        for (int i = 0; i < length; ++i) {
            Polygonal pivot = polygonals.get(i);
            for (int j = i + 1; j < length; ++j) {
                Polygonal polygonal = polygonals.get(j);
                if (pivot.step != polygonal.step) {
                    if (pivot.tail == polygonal.head) {
                        edges[i][j] = 1;
                    }
                    if (polygonal.tail == pivot.head) {
                        edges[j][i] = 1;
                    }
                }
            }
        }

        List<Integer> indexes = new ArrayList<>();
        boolean[] steps = new boolean[target];
        Arrays.fill(steps, false);
        int pivot = polygonals.get(0).step;
        steps[pivot] = true;
        for (int i = 0; i < length; ++i) {
            indexes.add(i);
            int step = polygonals.get(i).step;
            if (step != pivot) {
                return;
            }
            search(polygonals, edges, i, indexes, steps, target);
            indexes.remove(indexes.size() - 1);
        }
    }

    private void addTriangle(List<Polygonal> polygonals) {
        int start = (int) Math.ceil((Math.sqrt(8001) - 1) / 2);
        int end = (int) Math.ceil((Math.sqrt(80001) - 1) / 2);
        for (int i = start; i < end; ++i) {
            int value = i * (i + 1) >> 1;
            if (value % 100 >= 10) {
                polygonals.add(new Polygonal(value, 0));
            }
        }
    }

    private void addSquare(List<Polygonal> polygonals) {
        int start = (int) Math.ceil(Math.sqrt(1000));
        int end = (int) Math.ceil(Math.sqrt(10000));
        for (int i = start; i < end; ++i) {
            int value = i * i;
            if (value % 100 >= 10) {
                polygonals.add(new Polygonal(value, 1));
            }
        }
    }

    private void addPentagonal(List<Polygonal> polygonals) {
        int start = (int) Math.ceil((Math.sqrt(24001) + 1) / 6);
        int end = (int) Math.ceil((Math.sqrt(240001) + 1) / 6);
        for (int i = start; i < end; ++i) {
            int value = i * (3 * i - 1) >> 1;
            if (value % 100 >= 10) {
                polygonals.add(new Polygonal(value, 2));
            }
        }
    }

    private void addHexagonal(List<Polygonal> polygonals) {
        int start = (int) Math.ceil((Math.sqrt(8001) + 1) / 4);
        int end = (int) Math.ceil((Math.sqrt(80001) + 1) / 4);
        for (int i = start; i < end; ++i) {
            int value = i * ((i << 1) - 1);
            if (value % 100 >= 10) {
                polygonals.add(new Polygonal(value, 3));
            }
        }
    }

    private void addHeptagonal(List<Polygonal> polygonals) {
        int start = (int) Math.ceil((Math.sqrt(40009) + 3) / 10);
        int end = (int) Math.ceil((Math.sqrt(400009) + 3) / 10);
        for (int i = start; i < end; ++i) {
            int value = i * (5 * i - 3) >> 1;
            if (value % 100 >= 10) {
                polygonals.add(new Polygonal(value, 4));
            }
        }
    }

    private void addOctagonal(List<Polygonal> polygonals) {
        int start = (int) Math.ceil((Math.sqrt(12002) + 2) / 6);
        int end = (int) Math.ceil((Math.sqrt(120002) + 2) / 6);
        for (int i = start; i < end; ++i) {
            int value = i * (3 * i - 2);
            if (value % 100 >= 10) {
                polygonals.add(new Polygonal(value, 5));
            }
        }
    }

    private void search(List<Polygonal> polygonals, int[][] edges, int start, List<Integer> indexes, boolean[] steps, int target) {
        if (indexes.size() == target) {
            if (polygonals.get(indexes.get(0)).head == polygonals.get(indexes.get(target - 1)).tail) {
                int result = 0;
                for (int index : indexes) {
                    Polygonal polygonal = polygonals.get(index);
                    result += polygonal.head * 100 + polygonal.tail;
                }
                System.out.println(result);
            }
            return;
        }

        for (int i = polygonals.size() - 1; i >= 0; --i) {
            if (0 != edges[start][i]) {
                int step = polygonals.get(i).step;
                if (!steps[step]) {
                    indexes.add(i);
                    steps[step] = true;
                    search(polygonals, edges, i, indexes, steps, target);
                    indexes.remove(indexes.size() - 1);
                    steps[step] = false;
                }
            }
        }
    }

    private static class Polygonal {
        public int head;
        public int tail;
        public int step;

        public Polygonal(int value, int step) {
            this.head = value / 100;
            this.tail = value % 100;
            this.step = step;
        }
    }
}

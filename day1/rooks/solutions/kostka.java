import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Deque;

public class rooks {

    private static class DistValue {
        int dist;
        int val;

        DistValue(int dist, int val) {
            this.dist = dist;
            this.val = val;
        }
    }

    public static int[][] calculate_moves(int[][] A, int K) {
        int N = A.length;
        int M = A[0].length;
        int totalElements = N * M;

        int[][] pos = new int[totalElements + 1][2];
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < M; c++) {
                pos[A[r][c]][0] = r;
                pos[A[r][c]][1] = c;
            }
        }

        final int INF = Integer.MAX_VALUE;
        int[] dist = new int[totalElements + 1];
        Arrays.fill(dist, INF);

        if (totalElements > 0) {
            dist[1] = 0;
        }

        Deque<DistValue>[] rowDeques = new ArrayDeque[N];
        Deque<DistValue>[] colDeques = new ArrayDeque[M];
        for (int i = 0; i < N; i++) {
            rowDeques[i] = new ArrayDeque<>();
        }
        for (int i = 0; i < M; i++) {
            colDeques[i] = new ArrayDeque<>();
        }

        if (totalElements > 0) {
            int startR = pos[1][0];
            int startC = pos[1][1];
            rowDeques[startR].addLast(new DistValue(0, 1));
            colDeques[startC].addLast(new DistValue(0, 1));
        }

        for (int val = 2; val <= totalElements; val++) {
            int r = pos[val][0];
            int c = pos[val][1];

            int minMoves = INF;

            Deque<DistValue> rowDeque = rowDeques[r];
            while (!rowDeque.isEmpty() && rowDeque.peekFirst().val < val - K) {
                rowDeque.pollFirst();
            }
            if (!rowDeque.isEmpty()) {
                int predDist = rowDeque.peekFirst().dist;
                if (predDist != INF) {
                    minMoves = Math.min(minMoves, predDist + 1);
                }
            }

            Deque<DistValue> colDeque = colDeques[c];
            while (!colDeque.isEmpty() && colDeque.peekFirst().val < val - K) {
                colDeque.pollFirst();
            }
            if (!colDeque.isEmpty()) {
                int predDist = colDeque.peekFirst().dist;
                if (predDist != INF) {
                    minMoves = Math.min(minMoves, predDist + 1);
                }
            }
            
            dist[val] = minMoves;

            if (dist[val] != INF) {
                while (!rowDeque.isEmpty() && rowDeque.peekLast().dist >= dist[val]) {
                    rowDeque.pollLast();
                }
                rowDeque.addLast(new DistValue(dist[val], val));

                while (!colDeque.isEmpty() && colDeque.peekLast().dist >= dist[val]) {
                    colDeque.pollLast();
                }
                colDeque.addLast(new DistValue(dist[val], val));
            }
        }

        int[][] resultMatrix = new int[N][M];
        for (int i = 1; i <= totalElements; i++) {
            int r = pos[i][0];
            int c = pos[i][1];
            resultMatrix[r][c] = (dist[i] == INF) ? -1 : dist[i];
        }

        return resultMatrix;
    }
}
import java.util.LinkedList;
import java.util.Queue;

public class rooks {

    public static int[][] calculate_moves(int[][] A, int K) {
        int N = A.length;
        int M = A[0].length;

        int[][] dist = new int[N][M];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                dist[i][j] = -1;
            }
        }

        Queue<int[]> q = new LinkedList<>();
        int startR = -1, startC = -1;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (A[i][j] == 1) {
                    startR = i;
                    startC = j;
                    break;
                }
            }
            if (startR != -1) {
                break;
            }
        }

        dist[startR][startC] = 0;
        q.add(new int[]{startR, startC});

        while (!q.isEmpty()) {
            int[] current = q.poll();
            int r = current[0];
            int c = current[1];

            for (int rPrime = 0; rPrime < N; ++rPrime) {
                for (int cPrime = 0; cPrime < M; ++cPrime) {
                    if ((r == rPrime || c == cPrime) && (r != rPrime || c != cPrime)) {
                        if (A[rPrime][cPrime] - A[r][c] > 0 && A[rPrime][cPrime] - A[r][c] <= K) {
                            if (dist[rPrime][cPrime] == -1) {
                                dist[rPrime][cPrime] = dist[r][c] + 1;
                                q.add(new int[]{rPrime, cPrime});
                            }
                        }
                    }
                }
            }
        }
        return dist;
    }
}
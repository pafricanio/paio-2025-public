public class rooks {
    public static int[][] calculate_moves(int[][] A, int K) {
        int N = A.length;
        int M = A[0].length;
        int[][] moves = new int[N][M];
        for (int i=0; i<N; i++) {
            for (int j=0; j<M; j++) {
                moves[i][j] = 0;
            }
        }
        return moves;
    }
}
import java.util.Scanner;

public class grader {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);


        int N = sc.nextInt();
        int M = sc.nextInt();
        int K = sc.nextInt();

        int[][] A = new int[N][M];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                A[i][j] = sc.nextInt();
            }
        }

        int[][] moves = rooks.calculate_moves(A, K);

        assert moves.length == N;


        for (int i = 0; i < N; i++) {
            assert moves[i].length == M;
            for (int j = 0; j < M; j++) {
                System.out.print(moves[i][j] + (j == M - 1 ? "" : " "));
            }
            System.out.println();
        }
        sc.close();
    }
}

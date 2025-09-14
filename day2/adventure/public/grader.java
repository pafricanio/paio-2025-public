import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class grader {
    public static void main(String[] args) {
        BufferedReader br = new BufferedReader
          (new InputStreamReader(System.in));

        try(BufferedOutputStream bos = new BufferedOutputStream(System.out, 100000)){
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            int m = Integer.parseInt(st.nextToken());
            int q = Integer.parseInt(st.nextToken());

            int[] u = new int[m], v = new int[m], l = new int[m], r = new int[m];
            int[] u2 = new int[q], v2 = new int[q], l2 = new int[q], r2 = new int[q];

            for(int i = 0; i < m; ++i){
                st = new StringTokenizer(br.readLine());
                u[i] = Integer.parseInt(st.nextToken());
                v[i] = Integer.parseInt(st.nextToken());
                l[i] = Integer.parseInt(st.nextToken());
                r[i] = Integer.parseInt(st.nextToken());
            }

            for(int i = 0; i < q; ++i){
                st = new StringTokenizer(br.readLine());
                u2[i] = Integer.parseInt(st.nextToken());
                v2[i] = Integer.parseInt(st.nextToken());
                l2[i] = Integer.parseInt(st.nextToken());
                r2[i] = Integer.parseInt(st.nextToken());
            }

            boolean[] ans = adventure.add_roads(n, m, q, u, v, l, r, u2, v2, l2, r2);
            for(int i = 0; i < ans.length; ++i){
                bos.write((ans[i] ? "1\n" : "0\n").getBytes());
            }
            int[] ans2 = adventure.assign_times();

            for(int i = 0; i < ans2.length; ++i){
                bos.write((String.valueOf(ans2[i]) + "\n").getBytes());
            }
            bos.flush();
        }
        catch (Exception e) {
        }
    }
};

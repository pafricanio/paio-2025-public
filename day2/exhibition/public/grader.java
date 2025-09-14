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

            int[] a = new int[n], b = new int[n], s = new int[m];

            st = new StringTokenizer(br.readLine());
            for(int i = 0; i < n; ++i)
                a[i] = Integer.parseInt(st.nextToken());

            st = new StringTokenizer(br.readLine());
            for(int i = 0; i < n; ++i)
                b[i] = Integer.parseInt(st.nextToken());

            st = new StringTokenizer(br.readLine());
            for(int i = 0; i < m; ++i)
                s[i] = Integer.parseInt(st.nextToken());

            bos.write((String.valueOf(exhibition.max_paintings(n, m, a, b, s)) + "\n").getBytes());
            bos.flush();
        }
        catch (Exception e) {
        }
    }
};

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
            int t = Integer.parseInt(st.nextToken());
            for(int i = 0; i < t; i++){
                st = new StringTokenizer(br.readLine());

                int n = Integer.parseInt(st.nextToken());
                int m = Integer.parseInt(st.nextToken());

                bos.write((String.valueOf(cake.count_square_cakes(n, m)) + "\n").getBytes());
            }
            bos.flush();
        }
        catch (Exception e) {
        }
    }
};

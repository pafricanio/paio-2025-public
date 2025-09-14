import java.util.Scanner;

public class grader {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        int n = sc.nextInt();
        
        long[] a = new long[n - 1];
        for (int i = 0; i < n - 1; i++) {
            a[i] = sc.nextLong();
        }
        
        XorResult result = xor.find_multiset(n, a);
        
        System.out.println(result.xorValue);
        System.out.println(result.multiset.size());
        for (int i = 0; i < result.multiset.size(); i++) {
            if (i > 0) System.out.print(" ");
            System.out.print(result.multiset.get(i));
        }
        if (!result.multiset.isEmpty()) System.out.println();
        
        sc.close();
    }
}
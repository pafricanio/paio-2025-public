import java.util.*;

class XorResult {
    long xorValue;
    List<Integer> multiset;
    
    XorResult(long xorValue, List<Integer> multiset) {
        this.xorValue = xorValue;
        this.multiset = multiset;
    }
}

public class xor {
    public static XorResult find_multiset(int n, long[] a) {
        long xorValue = a[0];
        List<Integer> multiset = new ArrayList<>();
        multiset.add(1);
        multiset.add(2);
        
        return new XorResult(xorValue, multiset);
    }
}
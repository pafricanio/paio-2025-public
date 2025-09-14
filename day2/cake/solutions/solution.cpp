// @check-accepted: examples N3 TNsmall Nsmall TsmallNmid main
#include "cake.h"

int count_square_cakes(int N, int M) {
    int ans = 0;
    while (N > 0 && M > 0) {
        if (N < M) std::swap(N, M);
        ans += N / M;
        N %= M;
    }
    return ans;
}

// @check-accepted: examples N3 TNsmall Nsmall TsmallNmid
// @check-time-limit-exceeded: main
#include "cake.h"

int count_square_cakes(int N, int M) {
    long long ans = 0;
    while (N > 0 && M > 0) {
        if (N < M) std::swap(N, M);
        for (; N >= M; N -= M) ans++;
    }
    return ans;
}

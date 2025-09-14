// @check-accepted: examples N3 TNsmall Nsmall TsmallNmid
// @check-time-limit-exceeded: main

#include "cake.h"

int count_square_cakes(int N, int M) {
  if (N < M) {
    return count_square_cakes(M, N);
  }
  if (M == 0) {
    return 0;
  }
  return count_square_cakes(N - M, M) + 1;
}

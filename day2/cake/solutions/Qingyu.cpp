/*
* Author: Qingyu
* Description: 100pts
*/

#include "cake.h"

int count_square_cakes(int N, int M) {
  if (N < M) std::swap(N, M);
  if (N == 0 || M == 0) return 0;
  return N / M + count_square_cakes(N % M, M);
}
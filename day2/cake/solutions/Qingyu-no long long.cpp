/*
* Author: Qingyu
* Description: in case contestant forgot to use long long for some reason
*/

#include "cake.h"

int count_square_cakes(int N, int M) {
  if (N < M) std::swap(N, M);
  if (N == 0 || M == 0) return 0;
  return (int)(N / M + count_square_cakes(N % M, M));
}
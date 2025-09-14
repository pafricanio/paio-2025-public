# Author: Qingyu
# Description: 100pts

def count_square_cakes(N, M):
  if N < M:
    N, M = M, N
  if M == 0:
    return 0
  return N // M + count_square_cakes(N % M, M)
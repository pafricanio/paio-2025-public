// @check-accepted: examples small
// @check-wrong-answer: S_larger B_equal medium large
#include "exhibition.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
#define INF 1e15

int max_paintings(int N, int M, vector<int> A, vector<int> B, vector<int> S) {
  if (N > 20 || M > 20) {
    cout << "0\n";
    return 0;
  }

  vector<pair<ll, ll>> pairs(N);
  for (int i = 0; i < N; ++i) {
    pairs[i] = { A[i], B[i] };
  }
  sort(pairs.begin(), pairs.end());
  for (int i = 0; i < N; ++i) {
    A[i] = pairs[i].first;
    B[i] = pairs[i].second;
  }

  sort(S.begin(), S.end());

  int best = 0;
  for (int maskI = 0; maskI < (1 << N); ++maskI) {
    for (int maskJ = 0; maskJ < (1 << M); ++maskJ) {
      if (__builtin_popcount(maskI) != __builtin_popcount(maskJ)) continue;
      int cnt = __builtin_popcount(maskI);
      ll prevA = -INF;
      ll prevB = -INF;

      int i = 0, j = 0, k;
      for (k = 0; k < cnt; ++k) {
        while (!(maskI & (1 << i))) ++i;
        while (!(maskJ & (1 << j))) ++j;
        if (A[i] > S[j] || A[i] < prevA || B[i] < prevB) {
          k = -1;
          break;
        }
        prevA = A[i];
        prevB = B[i];
        i++; j++;
      }

      if (k != cnt)
        continue;

      best = max(best, __builtin_popcount(maskI));
    }
  }

  return best;
}

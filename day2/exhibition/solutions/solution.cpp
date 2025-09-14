// @check-accepted: examples small S_larger B_equal medium large
#include "exhibition.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define INF (1000000009)

int max_paintings(int N, int M, vector<int> A, vector<int> B, vector<int> S) {
  vector<pair<int, int>> pairs(N);
  for (int i = 0; i < N; ++i) {
    pairs[i] = { A[i], B[i] };
  }
  
  sort(pairs.begin(), pairs.end());
  for (int i = 0; i < N; ++i) {
    A[i] = pairs[i].first;
    B[i] = pairs[i].second;
  }

  sort(S.begin(), S.end());
  vector<int> cap(N);
  for (int i = 0; i < N; ++i) {
    cap[i] = M - (lower_bound(S.begin(), S.end(), A[i]) - S.begin());
  }

  vector<int> dp(N + 1, -INF);
  dp[0] = INF;

  int best = 0;
  for (int i = N - 1; i >= 0; --i) {
    int limit = min(best, cap[i] - 1);
    int t = -1;
    if (limit >= 0) {
      auto it = upper_bound(dp.begin(), min(dp.begin() + (limit + 1), dp.end()), B[i],
                            [](const int& val, const int& elem) { return val > elem; });
      t = int(it - dp.begin()) - 1;
    }

    if (t >= 0) {
      dp[t + 1] = max(dp[t + 1], B[i]);
      best = max(best, t + 1);
    }
  }

  return best;
}

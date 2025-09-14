// @check-accepted: examples B_equal
// @check-wrong-answer: small S_larger medium large
#include "exhibition.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
#define INF (1e9+5)

int max_paintings(int N, int M, vector<int> A, vector<int> B, vector<int> S) {
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
    vector<int> cap(N);
    for (int i = 0; i < N; ++i) {
        cap[i] = M - (lower_bound(S.begin(), S.end(), A[i]) - S.begin());
    }

    int best = 0;
    for (int i = N - 1; i >= 0; --i) {
        if (cap[i] > best) {
            best++;
        }
    }

   return best;
}

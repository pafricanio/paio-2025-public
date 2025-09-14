// @check-accepted: S_larger
// @check-wrong-answer: examples small B_equal medium large
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

    ll best = 0;
    vector<ll> tails;
    tails.reserve(N);
    for (int i = 0; i < N; ++i) {
        auto it = upper_bound(tails.begin(), tails.end(), B[i]);
        if (it == tails.end()) tails.push_back(B[i]);
        else *it = B[i];
    }
    best = static_cast<ll>(min(S.size(), tails.size()));

    return best;
}

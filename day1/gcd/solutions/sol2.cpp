#include "gcd.h"
#include <bits/stdc++.h>
using namespace std;

static const int MOD = 998244353;
static const int BITS = 30;                 // since V <= 1e9 < 2^30
static const uint64_t TWO_POW_B = (1ULL << BITS);

static long long mod_pow(long long a, long long e, long long m) {
    long long r = 1 % m;
    a %= m;
    while (e > 0) {
        if (e & 1) r = (__int128)r * a % m;
        a = (__int128)a * a % m;
        e >>= 1;
    }
    return r;
}

int calculate_sum(int N, int K, int V, std::vector<int> A) {
    if (N <= 1) return 0;

    vector<int> pre(N + 1), suf(N + 2);
    {
        int g = 0;
        for (int i = 1; i <= N; ++i) {
            g = std::gcd(g, A[i - 1]);
            pre[i] = g;
        }
    }
    {
        int g = 0;
        for (int i = N; i >= 1; --i) {
            g = std::gcd(g, A[i - 1]);
            suf[i] = g;
        }
    }

    vector<int> uniqPre;
    uniqPre.reserve(64);
    int last = -1;
    for (int i = 1; i <= N; ++i) {
        if (pre[i] != last) {
            uniqPre.push_back(pre[i]);
            last = pre[i];
        }
    }
    int P = (int)uniqPre.size();
    unordered_map<int,int> preId;
    preId.reserve(P * 2);
    for (int i = 0; i < P; ++i) preId[uniqPre[i]] = i;

    long long V1 = (long long)V + 1;
    array<long long, BITS> ones{};
    for (int b = 0; b < BITS; ++b) {
        long long period = 1LL << (b + 1);
        long long full = V1 / period;
        long long rem  = V1 % period;
        ones[b] = full * (1LL << b) + max(0LL, rem - (1LL << b));
    }

    struct CacheVal { int fmod; int y_low; int y_mod; };
    unordered_map<int, CacheVal> fCache;
    fCache.reserve(256);

    auto get_sum_xor = [&](int g)->int {
        auto it = fCache.find(g);
        if (it != fCache.end()) return it->second.fmod;

        int y_low = (int)mod_pow(g, K, TWO_POW_B);
        int y_mod = (int)mod_pow(g, K, MOD);

        long long y_high_mod = ( (long long)y_mod - (long long)(y_low % MOD) ) % MOD;
        if (y_high_mod < 0) y_high_mod += MOD;
        long long term_high = (y_high_mod * (V1 % MOD)) % MOD;

        long long term_low = 0;
        for (int b = 0; b < BITS; ++b) {
            long long cnt1 = ((y_low >> b) & 1) ? (V1 - ones[b]) : ones[b];
            term_low += (cnt1 % MOD) * ((1LL << b) % MOD) % MOD;
            if (term_low >= (long long)MOD) term_low %= MOD;
        }

        int fmod = (int)((term_high + term_low) % MOD);
        fCache.emplace(g, CacheVal{fmod, y_low, y_mod});
        return fmod;
    };

    vector<long long> cnt(P, 0), sumA(P, 0);   // modulo sum for sumA
    cnt[ preId[pre[1]] ] = 1;
    sumA[ preId[pre[1]] ] = A[0] % MOD;

    long long answer = 0;

    for (int j = 2; j <= N; ++j) {
        int s = suf[j];
        long long Aj = A[j - 1] % MOD;

        long long add = 0;
        for (int idx = 0; idx < P; ++idx) {
            if (cnt[idx] == 0) continue;
            int Pval = uniqPre[idx];
            int g = std::gcd(Pval, s);
            int Fx = get_sum_xor(g);  // sum_{x=0..V} ( (g^K) XOR x ) mod MOD

            long long left_sum  = sumA[idx];               // sum over A[i] in this group
            long long right_sum = (Aj * (cnt[idx] % MOD)) % MOD;
            long long contrib = ( (long long)Fx * ((left_sum + right_sum) % MOD) ) % MOD;
            add += contrib;
            if (add >= (long long)MOD) add %= MOD;
        }

        answer += add;
        if (answer >= (long long)MOD) answer %= MOD;

        int id = preId[pre[j]];
        cnt[id] += 1;
        sumA[id] += A[j - 1];
        if (sumA[id] >= MOD) sumA[id] -= MOD;
    }

    return (int)(answer % MOD);
}

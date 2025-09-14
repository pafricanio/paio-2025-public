#include "gcd.h"
#include <bits/stdc++.h>

constexpr int mod = 998244353;

inline int mul(int x, int y) { return 1ll * x * y % mod; }

inline int fastpow(int x, int p) {
    int r = 1;
    while (p) {
        if (p & 1) r = mul(r, x);
        x = mul(x, x);
        p >>= 1;
    }
    return r;
}

int calculate_sum(int n, int k, int V, std::vector<int> a) {
  int res = 0;
  std::vector<int> pre(n), suf(n);
  pre[0] = a[0]; suf[n - 1] = a[n - 1];
  for (int i = 1; i < n; i++) {
    pre[i] = std::gcd(pre[i - 1], a[i]);
  }
  for (int i = n - 2; i >= 0; i--) {
    suf[i] = std::gcd(suf[i + 1], a[i]);
  }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int g = std::gcd(pre[i], suf[j]), s = (a[i] + a[j]) % mod;
            int z = fastpow(g, k); // note: this will be wrong if g^k is huge, as (g^k xor x) % mod != (g^k % mod xor x) % mod
            for (int x = 0; x <= V; x++) {
                int w = (z ^ x) % mod;
                res = (res + 1ll * w * s) % mod;
            }
        }
    }
  return res;
}
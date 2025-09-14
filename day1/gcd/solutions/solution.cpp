#include <bits/stdc++.h>
#include "gcd.h"
using namespace std;

const long long maxn = 5e5 + 10;
const long long mod = 998244353;
long long n, k, V, a[maxn], suf[maxn], pre[maxn], f[maxn], res, g[maxn], h[maxn];
vector<long long> vec[maxn];
unordered_map<long long, long long> ans;
long long quickpow(long long x, long long y, long long pmod = mod)
{
    long long p = 1;
    for (int i = y; i; i >>= 1)
        p = p * ((i & 1) ? x : 1) % pmod, x = (x * x) % pmod;
    return p;
}
long long calc(long long x)
{
    long long s = 0;
    if (ans.find(x) != ans.end())
        return ans[x];
    for (int i = 29; ~i; i--)
    {
        long long num = (V + 1) / (1 << (i + 1)), c = (num << i) + max(0ll, (V + 1) % (1 << (i + 1)) - (1 << i));
        if (x & (1 << i))
            s = (s + (V + 1 - c) * (1 << i)) % mod;
        else
            s = (s + c * (1 << i)) % mod;
    }
    return ans[x] = s;
}
long long v(int i, long long j)
{
    long long knum = quickpow(gcd(pre[j], suf[i]), k, (1 << 30)), num = quickpow(gcd(pre[j], suf[i]), k);
    return (calc(knum) + (num - knum + mod) * (V + 1)) % mod;
}
int calculate_sum(int _N, int _K, int _V, std::vector<int> _a)
{
    n = _N;
    k = _K;
    V = _V;
    for (int i = 1; i <= n; i++)
        a[i] = _a[i - 1];
    for (int i = 1; i <= n; i++)
        pre[i] = std::gcd(pre[i - 1], a[i]);
    for (int i = n; i; i--)
        suf[i] = std::gcd(suf[i + 1], a[i]);
    for (int i = n; i; i--)
    {
        if (suf[i] == suf[i + 1])
        {
            if (suf[i + 1] != suf[i + 2])
                h[i] = v(i + 1, i);
            else
                h[i] = h[i + 1];
            g[i] = (g[i + 1] - h[i] + mod) % mod;
            f[i] = (f[i + 1] - h[i] * (a[i] + a[i + 1]) % mod + mod) % mod;
            f[i] = (f[i] + g[i] * (a[i] - a[i + 1]) % mod + mod) % mod;
        }
        else
        {
            long long now = 0;
            for (long long j = 1; j < i; j++)
            {
                if (pre[j] != pre[j - 1])
                    now = v(i, j);
                f[i] = (f[i] + now * (a[i] + a[j])) % mod;
                g[i] = (g[i] + now) % mod;
            }
        }
        res = (res + f[i]) % mod;
    }
    return res;
}
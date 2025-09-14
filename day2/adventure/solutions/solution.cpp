#include <bits/stdc++.h>
#include "adventure.h"
#define rep(x, y, z) for(ll x = (y); x <= (z); ++x)
#define per(x, y, z) for(ll x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(y < x) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

template<int mod>
inline unsigned int down(unsigned int x) {
    return x >= mod ? x - mod : x;
}

template<int mod>
struct Modint {
    unsigned int x;
    Modint() = default;
    Modint(unsigned int x) : x(x) {}
    friend istream& operator>>(istream& in, Modint& a) {return in >> a.x;}
    friend ostream& operator<<(ostream& out, Modint a) {return out << a.x;}
    friend Modint operator+(Modint a, Modint b) {return down<mod>(a.x + b.x);}
    friend Modint operator-(Modint a, Modint b) {return down<mod>(a.x - b.x + mod);}
    friend Modint operator*(Modint a, Modint b) {return 1ULL * a.x * b.x % mod;}
    friend Modint operator/(Modint a, Modint b) {return a * ~b;}
    friend Modint operator^(Modint a, int b) {Modint ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
    friend Modint operator~(Modint a) {return a ^ (mod - 2);}
    friend Modint operator-(Modint a) {return down<mod>(mod - a.x);}
    friend Modint& operator+=(Modint& a, Modint b) {return a = a + b;}
    friend Modint& operator-=(Modint& a, Modint b) {return a = a - b;}
    friend Modint& operator*=(Modint& a, Modint b) {return a = a * b;}
    friend Modint& operator/=(Modint& a, Modint b) {return a = a / b;}
    friend Modint& operator^=(Modint& a, int b) {return a = a ^ b;}
    friend Modint& operator++(Modint& a) {return a += 1;}
    friend Modint operator++(Modint& a, int) {Modint x = a; a += 1; return x;}
    friend Modint& operator--(Modint& a) {return a -= 1;}
    friend Modint operator--(Modint& a, int) {Modint x = a; a -= 1; return x;}
    friend bool operator==(Modint a, Modint b) {return a.x == b.x;}
    friend bool operator!=(Modint a, Modint b) {return !(a == b);}
};

const ll N = 505, inf = 0x3f3f3f3f3f3f3f3fll;

ll n, m, q, f[N][N], g[N][N];
vector<tuple<ll, ll>> G;

std::vector<bool> add_roads(int N, int M, int Q, std::vector<int> U, std::vector<int> V, std::vector<int> L, std::vector<int> R, std::vector<int> U2, std::vector<int> V2, std::vector<int> L2, std::vector<int> R2) {
    n = N, m = M, q = Q;

    rep(u, 1, n) rep(v, 1, n) f[u][v] = u == v ? 0LL : +inf;
    rep(i, 1, m) {
        ll u = U[i - 1] + 1, v = V[i - 1] + 1, l = L[i - 1], r = R[i - 1];
		assert(v==u+1);
        chkmin(f[u][v], r);
        chkmin(f[v][u], -l);
        G.emplace_back(u, v);
    }
    rep(w, 1, n) rep(u, 1, n) rep(v, 1, n) if(f[u][w] < +inf && f[w][v] < +inf) chkmin(f[u][v], f[u][w] + f[w][v]);
    std::vector<bool> res(q);
    rep(i, 1, q) {
        ll s = U2[i - 1] + 1, t = V2[i - 1] + 1, l = L2[i - 1], r = R2[i - 1];
		assert(t==s+1);
        rep(u, 1, n) rep(v, 1, n) g[u][v] = f[u][v];
        rep(u, 1, n) rep(v, 1, n) if(g[u][s] < +inf && g[t][v] < +inf) chkmin(g[u][v], g[u][s] + r + g[t][v]);
        rep(u, 1, n) rep(v, 1, n) if(g[u][t] < +inf && g[s][v] < +inf) chkmin(g[u][v], g[u][t] - l + g[s][v]);
        bool ok = true;
        rep(u, 1, n) if(g[u][u] < 0) ok = false;
        res[i - 1] = ok;
        if(ok) {
            rep(u, 1, n) rep(v, 1, n) f[u][v] = g[u][v];
            G.emplace_back(s, t);
        }
    }
    return res;
}

std::vector<int> assign_times() {
    std::vector<int> res;
    for (auto [u, v]: G) res.push_back(f[1][v] - f[1][u]);
    return res;
}


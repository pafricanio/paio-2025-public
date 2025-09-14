#include "adventure.h"
#include <bits/stdc++.h>
using namespace std;

namespace {
    using int64 = long long;
    const int MAXN = 505;
    const int64 INF = (1LL<<62);

    int N_global = 0;
    static int64 F[MAXN][MAXN];

    struct Edge {
        int u, v;
        int l, r;
    };
    vector<Edge> edges_final;  
}

vector<bool> add_roads(int N, int M, int Q,
    vector<int> U, vector<int> V,
    vector<int> L, vector<int> R,
    vector<int> U2, vector<int> V2,
    vector<int> L2, vector<int> R2)
{
    N_global = N;
    edges_final.clear();

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) F[i][j] = (i == j ? 0 : INF);
    }

    edges_final.reserve((size_t)M);
    for (int i = 0; i < M; ++i) {
        int u = U[i], v = V[i], l = L[i], r = R[i];
        if (R[i] < F[u][v]) F[u][v] = R[i];     
        if (-L[i] < F[v][u]) F[v][u] = -L[i];    
        edges_final.push_back({u, v, l, r});
    }

    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) if (F[i][k] < INF) {
            for (int j = 0; j < N; ++j) if (F[k][j] < INF) {
                int64 cand = F[i][k] + F[k][j];
                if (cand < F[i][j]) F[i][j] = cand;
            }
        }
    }

    vector<bool> accepted(Q, false);
    edges_final.reserve(edges_final.size() + (size_t)Q);

    static int64 G[MAXN][MAXN];
    for (int q = 0; q < Q; ++q) {
        int s = U2[q], t = V2[q], l = L2[q], r = R2[q];

        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                G[i][j] = F[i][j];

        for (int u = 0; u < N; ++u) if (F[u][s] < INF) {
            int64 base = F[u][s] + (int64)r;
            for (int v = 0; v < N; ++v) if (F[t][v] < INF) {
                int64 cand = base + F[t][v];
                if (cand < G[u][v]) G[u][v] = cand;
            }
        }
        for (int u = 0; u < N; ++u) if (F[u][t] < INF) {
            int64 base = F[u][t] - (int64)l;
            for (int v = 0; v < N; ++v) if (F[s][v] < INF) {
                int64 cand = base + F[s][v];
                if (cand < G[u][v]) G[u][v] = cand;
            }
        }

        bool ok = true;
        for (int i = 0; i < N; ++i) {
            if (G[i][i] < 0) { ok = false; break; }
        }

        if (ok) {
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    F[i][j] = G[i][j];
            edges_final.push_back({s, t, l, r});
            accepted[q] = true;
        } else {
            accepted[q] = false;
        }
    }

    return accepted;
}

vector<int> assign_times() {
    vector<int> times;
    times.reserve(edges_final.size());

    for (const auto &e : edges_final) {
        long long t = F[0][e.v] - F[0][e.u];
        times.push_back((int)t);
    }
    return times;
}

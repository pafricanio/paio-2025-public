#include "adventure.h"
#include <iostream>
#include <vector>

int main() {
    int N, M, Q;
    std::cin >> N >> M >> Q;

    std::vector<int> U(M), V(M), L(M), R(M);
    std::vector<int> U2(Q), V2(Q), L2(Q), R2(Q);

    for (int i = 0; i < M; ++i) std::cin >> U[i] >> V[i] >> L[i] >> R[i];
    for (int i = 0; i < Q; ++i) std::cin >> U2[i] >> V2[i] >> L2[i] >> R2[i];

    std::vector<bool> ans = add_roads(N, M, Q, U, V, L, R, U2, V2, L2, R2);
    for (int i = 0; i < ans.size(); ++i) std::cout << (int)(ans[i]) << '\n';

    std::vector<int> ans2 = assign_times();
    for (int i = 0; i < ans2.size(); ++i) std::cout << ans2[i] << '\n';
    return 0;
}

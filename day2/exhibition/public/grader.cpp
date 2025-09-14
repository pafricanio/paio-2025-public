#include "exhibition.h"
#include <iostream>
#include <vector>

int main() {
    int N, M;
    std::cin >> N >> M;

    std::vector<int> A(N), B(N), S(M);
    for (int i = 0; i < N; ++i) std::cin >> A[i];
    for (int i = 0; i < N; ++i) std::cin >> B[i];
    for (int i = 0; i < M; ++i) std::cin >> S[i];

    std::cout << max_paintings(N, M, A, B, S) << std::endl;
    return 0;
}

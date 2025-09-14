#include "gcd.h"
#include <iostream>

int main() {
    int N, K, V;
    std::cin >> N >> K >> V;
    std::vector<int> A(N);
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }
    std::cout << calculate_sum(N, K, V, A) << '\n';
    return 0;
}

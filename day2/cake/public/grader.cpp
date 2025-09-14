#include "cake.h"
#include <iostream>
#include <vector>

int main() {
    int T;
    std::cin >> T;
    for (int i = 0; i < T; i++) {
        int N, M;
        std::cin >> N >> M;
        std::cout << count_square_cakes(N, M) << std::endl;
    }

    return 0;
}

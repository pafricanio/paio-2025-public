#include "cards.h"
#include <iostream>

int main() {
    int T;
    std::cin >> T;
    for (int i = 0; i < T; i++) {
        int X, Y, Z;
        std::cin >> X >> Y >> Z;
        std::cout << maximum_score(X, Y, Z) << '\n';
    }
    return 0;
}

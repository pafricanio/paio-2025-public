#include <iostream>
#include <vector>
#include "xor.h"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<long long int> a(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> a[i];
    }
    
    auto result = find_multiset(n, a);
    
    cout << result.first << '\n';  // XOR value
    cout << result.second.size() << '\n';  // Size of multiset
    for (int i = 0; i < (int)result.second.size(); i++) {
        if (i > 0) cout << ' ';
        cout << result.second[i];
    }
    if (!result.second.empty()) cout << '\n';
    
    return 0;
}

/**
 *    author:  BERNARD B.01
**/
#include "cards.h"
#include <bits/stdc++.h>

using namespace std;

long long maximum_score(int x, int y, int z) {
  int ans = 0;
  while (x > 0 && y > 0 && z > 0) {
    ans += 1;
    int mn = min({x, y, z});
    if (x == mn) {
      y--; z--;
    } else if (y == mn) {
      x--; z--;
    } else {
      x--; y--;
    }
  }
  return ans;
}

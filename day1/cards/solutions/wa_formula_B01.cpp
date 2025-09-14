/**
 *    author:  BERNARD B.01
**/
#include "cards.h"
#include <bits/stdc++.h>

using namespace std;

long long maximum_score(int X, int Y, int Z) {
  return (X + Y + Z - 1LL) / 2;
}
// 1 2 3 1 2 3 1 2 3
// 0 0 1 0 1 0 1 0 1

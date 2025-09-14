/*
* Author: Qingyu
* Description: Standard solution
*/
#include "cards.h"

#include <vector>
#include <algorithm>

long long maximum_score(int _X, int _Y, int _Z) {
  long long X = _X, Y = _Y, Z = _Z;
  --X; --Y; --Z;
  if (X > Y) std::swap(X, Y);
  if (X > Z) std::swap(X, Z);
  if (Y > Z) std::swap(Y, Z);

  return 1 + std::min(std::min((X + Y + Z) / 2, X * 2 + 1), Y * 2);
}

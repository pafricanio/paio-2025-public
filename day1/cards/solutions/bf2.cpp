/*
* Author: Qingyu
* Description: Brute force by enumerating all card orders (dfs)
*/
#include "cards.h"
#include <vector>
#include <algorithm>

long long maxScore;

long long simulate(const std::vector<int>& order) {
  std::vector<int> stack;
  long long score = 0;
  for(int card : order) {
    stack.push_back(card);
    bool hasAll = true;
    for(int c = 0; c < 3; c++) {
      bool found = false;
      for(int s : stack) if(s == c) { found = true; break; }
      if(!found) { hasAll = false; break; }
    }
    if(hasAll) {
      stack.clear();
      stack.push_back(card);
      score++;
    }
  }
  return score;
}

void dfs(std::vector<int>& order, int x, int y, int z) {
  if(x == 0 && y == 0 && z == 0) {
    maxScore = std::max(maxScore, simulate(order));
    return;
  }
  if(x > 0) {
    order.push_back(0);
    dfs(order, x-1, y, z);
    order.pop_back();
  }
  if(y > 0) {
    order.push_back(1);
    dfs(order, x, y-1, z);
    order.pop_back();
  }
  if(z > 0) {
    order.push_back(2);
    dfs(order, x, y, z-1);
    order.pop_back();
  }
}

long long maximum_score(int X, int Y, int Z) {
  maxScore = 0;
  std::vector<int> order;
  dfs(order, X, Y, Z);
  return maxScore;
}

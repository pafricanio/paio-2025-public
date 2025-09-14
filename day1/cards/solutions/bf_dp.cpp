/*
* Author: Qingyu
* Description: Brute force by running dp
*/
#include "cards.h"
#include <vector>
#include <algorithm>

int memo[51][51][51][8];
bool visited[51][51][51][8];

int dp(int x, int y, int z, int mask) {
  if(x == 0 && y == 0 && z == 0) return 0;
  if(visited[x][y][z][mask]) return memo[x][y][z][mask];
  
  visited[x][y][z][mask] = true;
  int res = 0;
  
  if(x > 0) {
    int newMask = mask | 1;
    int score = (newMask == 7) ? 1 : 0;
    int nextMask = score ? 1 : newMask;
    res = std::max(res, score + dp(x-1, y, z, nextMask));
  }
  if(y > 0) {
    int newMask = mask | 2;
    int score = (newMask == 7) ? 1 : 0;
    int nextMask = score ? 2 : newMask;
    res = std::max(res, score + dp(x, y-1, z, nextMask));
  }
  if(z > 0) {
    int newMask = mask | 4;
    int score = (newMask == 7) ? 1 : 0;
    int nextMask = score ? 4 : newMask;
    res = std::max(res, score + dp(x, y, z-1, nextMask));
  }
  
  return memo[x][y][z][mask] = res;
}

long long maximum_score(int X, int Y, int Z) {
  return dp(X, Y, Z, 0);
}

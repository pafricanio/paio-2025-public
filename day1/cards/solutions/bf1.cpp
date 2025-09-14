/*
* Author: Qingyu
* Description: Brute force by enumerating card orders (next_permutation)
*/
#include "cards.h"
#include <vector>
#include <algorithm>

long long maximum_score(int X, int Y, int Z) {
  std::vector<int> cards;
  for(int i = 0; i < X; i++) cards.push_back(0);
  for(int i = 0; i < Y; i++) cards.push_back(1);
  for(int i = 0; i < Z; i++) cards.push_back(2);
  
  long long maxScore = 0;
  do {
    std::vector<int> stack;
    long long score = 0;
    for(int card : cards) {
      stack.push_back(card);
      bool hasAll = false;
      for(int c = 0; c < 3; c++) {
        bool found = false;
        for(int s : stack) if(s == c) { found = true; break; }
        if(!found) { hasAll = false; break; }
        hasAll = true;
      }
      if(hasAll) {
        stack.clear();
        stack.push_back(card);
        score++;
      }
    }
    maxScore = std::max(maxScore, score);
  } while(std::next_permutation(cards.begin(), cards.end()));
  return maxScore;
}

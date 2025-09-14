/*
* Author: Qingyu
* Description: Brute force but more stupid ( (X+Y+Z)! card orders )
*/
#include "cards.h"
#include <vector>
#include <algorithm>

long long maximum_score(int X, int Y, int Z) {
  std::vector<int> cards;
  for(int i = 0; i < X + Y + Z; i++) cards.push_back(i);
  
  long long maxScore = 0;
  do {
    std::vector<int> stack;
    long long score = 0;
    for(int _card : cards) {
      int card = (_card < X ? 0 : (_card < X + Y ? 1 : 2));
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

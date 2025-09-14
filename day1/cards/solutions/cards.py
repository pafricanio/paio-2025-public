# Author: Qingyu
# Description: Standard solution

def maximum_score(X, Y, Z):
  X -= 1
  Y -= 1
  Z -= 1
  if X > Y:
    X, Y = Y, X
  if X > Z:
    X, Z = Z, X
  if Y > Z:
    Y, Z = Z, Y
  return 1 + min(min((X + Y + Z) // 2, X * 2 + 1), Y * 2)
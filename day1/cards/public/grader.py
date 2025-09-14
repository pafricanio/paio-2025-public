import cards
import sys

T = int(input() )

for _ in range(T):
    a_str, b_str, c_str = input().split()
    a = int(a_str)
    b = int(b_str)
    c = int(c_str)

    result = cards.maximum_score(a, b, c)

    print(result)
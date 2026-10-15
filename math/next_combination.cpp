#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, K;

  vector<int> S(N, 0);
  ranges::fill(S | views::take(K), true);
  ranges::reverse(S);

  // next_permutationは辞書順でユニークな並びを順にたどるのですべて列挙できる
  do {
  } while (ranges::next_permutation(S).found);
};
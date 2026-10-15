#include <atcoder/segtree>
#include <cmath>
#include <vector>

const int INF = 0x3fffffff;

std::vector<int> LIS(const std::vector<int> &A) {
  std::vector<int> dp(A.size(), INF);

  for (const int x : A) {
    auto it = lower_bound(dp.begin(), dp.end(), x);
    *it = x;
  }

  return dp;
}

// A: 座標圧縮済み
// dp[i][j]: A の i 番目までを考慮したときの最後の要素が j となる LIS
std::vector<int> LIS(const std::vector<int> &A) {
  atcoder::segtree<int, [](int x, int y) { return std::max(x, y); }, []() { return 0; }> dp(std::vector<int>(A.size() + 1, -INF));
  dp.set(0, 0);

  for (const int x : A) {
    dp.set(x, dp.prod(0, x) + 1);
  }

  std::vector<int> res(A.size() + 1);
  for (int i = 0; i < ssize(res); i++) {
    res[i] = dp.get(i);
  }

  return res;
}
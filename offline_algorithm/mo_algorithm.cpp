#include <algorithm>
#include <cassert>
#include <cmath>
#include <ranges>
#include <vector>

// 計算量（平面に置き換えて考える, x 軸をブロックに分ける）
// ・B: ブロックサイズ, W: 区間の全体幅, N: クエリの数
// ・一つのブロック内の y 方向の移動: y 軸方向の最大の移動距離 W, ブロックの数 W / B -> W^2 / B
// ・一つのブロック内の x 方向の移動: x 軸方向の最大の移動距離 B, 地点間の移動 N -> N * B
// ・ブロックをまたぐ x 方向の移動: x 軸方向の最大の移動距離 2 * B, 移動回数 W / B -> 2 * W
// 相加相乗平均より、 B = \frac{W}{\sqrt{N}} が最適

// Reference (original implementation):
//   ei1333の日記: "Mo's akgorithm")
//   https://ei1333.hateblo.jp/entry/2017/09/11/211011
// Accessed: 2026-03-08
//
// Notes:
//   - Adapted to ACL-style monoid interface (S, op, e).

class Mo {
 private:
  int N, Q, block_size;

  std::vector<std::pair<int, int>> query;
  std::vector<int> idxs;

  bool qcomp(int a, int b) const {
    int ab = query[a].first / block_size;
    int bb = query[b].first / block_size;

    if (ab != bb) return ab < bb;

    // 典型テク：ブロックが偶数なら r 昇順、奇数なら r 降順
    if (ab % 2 == 0)
      return query[a].second < query[b].second;
    else
      return query[a].second > query[b].second;
  }

 public:
  Mo(int n) : N(n) {}

  // [l, r) として入れる
  void add(int l, int r) {
    query.emplace_back(l, r);
  }

  void build() {
    Q = ssize(query);
    assert(Q > 0);

    block_size = N / std::min(N, static_cast<int>(sqrt(Q)));
    idxs.resize(Q);

    std::ranges::iota(idxs, 0);

    std::ranges::sort(idxs, [this](int a, int b) { return qcomp(a, b); });
  }

  // ここを実装
  std::vector<int> solve(const std::vector<int> &A) {
    int l = 0, r = 0;
    for (auto idx : idxs) {
      while (l > query[idx].first);
      while (r < query[idx].second);
      while (l < query[idx].first);
      while (r > query[idx].second);
    }
  }
};
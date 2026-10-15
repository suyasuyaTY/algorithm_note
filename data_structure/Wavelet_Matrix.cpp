#include <bits/stdc++.h>

using namespace std;

struct BitVector {
  int n;
  vector<uint64_t> A;
  vector<uint64_t> rank64;
  BitVector() {}
  BitVector(int N) {
    n = (N + 63) / 64;
    A.resize(n + 1), rank64.resize(n + 1);
  }
  int popcnt(uint64_t x) { return __builtin_popcountll(x); }
  void set(int i) { A[i / 64] |= 1ull << (i & 63); }
  void build() {
    for (int i = 0; i < n; ++i) rank64[i + 1] = rank64[i] + popcnt(A[i]);
  }
  int rank(int i) {
    return rank64[i / 64] + popcnt(A[i / 64] & ((uint64_t(1) << (i & 63)) - 1));
  }
};

template <typename T>
struct Wavelet_Matrix {
  int H, N;
  vector<BitVector> dat;
  Wavelet_Matrix(int H, vector<T> A) : H(H), N(A.size()), dat(H) {
    for (int h = H - 1; h >= 0; --h) {
      // height h+1 to h.
      BitVector bv(N);
      vector<T> left, right;
      for (int i = 0; i < N; ++i) {
        int dir = A[i] >> h & 1;
        (dir == 0 ? left : right).emplace_back(A[i]);
        if (dir) bv.set(i);
      }
      int a = left.size(), b = right.size();
      for (int i = 0; i < a; ++i) A[i] = left[i];
      for (int i = 0; i < b; ++i) A[a + i] = right[i];
      bv.build();
      dat[h] = bv;
    }
  }

  // k-th (0-indexed) smallest number in a[L, R)
  T kth_smallest(int L, int R, int k) {
    assert(0 <= L && L < R && R <= N && 0 <= k && k < R - L);
    return kth_smallest_rec(H, L, R, k);
  }

  // k-th (0-indexed) largest number in a[L, R)
  T kth_largest(int L, int R, int k) {
    assert(0 <= L && L < R && R <= N && 0 <= k && k < R - L);
    return kth_smallest(L, R, R - L - k - 1);
  }

  // count i if (L <= i < R && lower <= A[i] < upper)
  int range_freq(int L, int R, T lower, T upper) {
    assert(0 <= L && L < R && R <= N && 0 <= lower && lower < upper);
    return range_freq(L, R, upper) - range_freq(L, R, lower);
  }

  // count i if (L <= i < R && A[i] < upper)
  int range_freq(int L, int R, T upper) {
    assert(0 <= L && L < R && R <= N && 0 <= upper);
    return range_freq_rec(H, L, R, 0, (T)1 << H, upper);
  }

  // max v[i] s.t. (l <= i < r) && (v[i] < upper)
  T prev_value(int l, int r, T upper) {
    int cnt = range_freq(l, r, upper);
    return cnt == 0 ? T(-1) : kth_smallest(l, r, cnt - 1);
  }

  // min v[i] s.t. (l <= i < r) && (lower <= v[i])
  T next_value(int l, int r, T lower) {
    int cnt = range_freq(l, r, lower);
    return cnt == r - l ? T(-1) : kth_smallest(l, r, cnt);
  }

 private:
  tuple<int, int, int, int> get_subtree_range(int h, int L, int R) {
    int a0 = L - dat[h].rank(L), a1 = dat[h].rank(L);
    int b0 = R - dat[h].rank(R), b1 = dat[h].rank(R);
    int c0 = N - dat[h].rank(N);
    return {a0, b0, c0 + a1, c0 + b1};
  }

  T kth_smallest_rec(int h, int l, int r, int k) {
    if (h == 0) return 0;
    auto [l0, r0, l1, r1] = get_subtree_range(h - 1, l, r);
    int left_size = r0 - l0;
    if (k < left_size) {
      return kth_smallest_rec(h - 1, l0, r0, k);
    } else {
      return ((T)1 << (h - 1)) + kth_smallest_rec(h - 1, l1, r1, k - left_size);
    }
  }

  int range_freq_rec(int h, int l, int r, T lower, T upper, T x) {
    // この部分木の値がすべて x 以上
    if (x <= lower) return 0;

    // この部分木の値がすべて x 未満
    if (upper <= x) return r - l;

    if (h == 0) return 0;

    auto [l0, r0, l1, r1] = get_subtree_range(h - 1, l, r);
    T mid = lower + (upper - lower) / 2;

    return range_freq_rec(h - 1, l0, r0, lower, mid, x) +
           range_freq_rec(h - 1, l1, r1, mid, upper, x);
  }
};
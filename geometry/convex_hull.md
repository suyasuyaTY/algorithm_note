# 凸包（Monotone Chain）

## 凸包とは

与えられた点群をすべて含む最小の凸多角形

## アルゴリズム

- 最後の頂点がlower_hullとupper_hullで被ることに注意
- 全点が縦一直線上にある場合
    - lowerとupperは同じ列になる
- 縦の辺を含む普通の凸包
    - lower_hullに右端の縦辺
    - upper_hullに左端の縦辺

```cpp
template <class T>
struct Point {
  T x, y;

  Point(T x = 0, T y = 0) : x(x), y(y) {}

  bool operator<(const Point &rhs) const {
    if (x != rhs.x) return x < rhs.x;
    return y < rhs.y;
  }

  bool operator==(const Point &rhs) const {
    return x == rhs.x && y == rhs.y;
  }
};

// AB と AC の外積
template <class T>
T cross_product(const Point<T> &A, const Point<T> &B, const Point<T> &C) {
  return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

// 下側凸包
// erase_collinear = true なら、同一直線上の中間点を消す
template <class T>
vector<Point<T>> lower_hull(vector<Point<T>> P, bool erase_collinear = true) {
  sort(P.begin(), P.end());
  P.erase(unique(P.begin(), P.end()), P.end());

  vector<Point<T>> res;

  for (const auto &p : P) {
    while ((int)res.size() >= 2) {
      auto a = res[(int)res.size() - 2];
      auto b = res[(int)res.size() - 1];

      T cr = cross_product(a, b, p);

      if (erase_collinear ? cr <= 0 : cr < 0) {
        res.pop_back();
      } else {
        break;
      }
    }

    res.push_back(p);
  }

  return res;
}

// 上側凸包
// erase_collinear = true なら、同一直線上の中間点を消す
template <class T>
vector<Point<T>> upper_hull(vector<Point<T>> P, bool erase_collinear = true) {
  sort(P.begin(), P.end());
  P.erase(unique(P.begin(), P.end()), P.end());

  vector<Point<T>> res;

  for (const auto &p : P) {
    while ((int)res.size() >= 2) {
      auto a = res[(int)res.size() - 2];
      auto b = res[(int)res.size() - 1];

      T cr = cross_product(a, b, p);

      if (erase_collinear ? cr >= 0 : cr > 0) {
        res.pop_back();
      } else {
        break;
      }
    }

    res.push_back(p);
  }

  return res;
}
```

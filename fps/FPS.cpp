#include <bits/stdc++.h>

#include <atcoder/all>

using namespace std;
using namespace atcoder;

// 形式的べき級数ライブラリ
//
// 想定:
// - mint は static_modint 系
// - 積は ACL の convolution を使うので、基本的には modint998244353 向け
//
// 基本的な使い方:
// FPS f = {1, 2, 3};          // 1 + 2x + 3x^2
// FPS g = {4, 5};             // 4 + 5x
// auto a = f + g;             // 和
// auto b = f - g;             // 差
// auto c = f * g;             // 積
// auto d = f.pre(5);          // 先頭 5 項を取得。足りない分は 0
// auto e = f.diff();          // 微分
// auto h = f.integral();      // 積分。積分定数は 0
//
// 高度な関数の前提:
// - inv(deg): f[0] != 0
// - log(deg): f[0] == 1
// - exp(deg): f[0] == 0
// - pow(k, deg): 一般の FPS に使える
//
// 使用例:
// FPS a = {1, 3, 2};
// auto ia = a.inv(6);         // 1 / a mod x^6
// auto la = a.log(6);         // log(a) mod x^6
//
// FPS b = {0, 1, 2};
// auto eb = b.exp(6);         // exp(b) mod x^6
// auto pb = b.pow(3, 6);      // b^3 mod x^6
//
// シフト:
// - (f >> k): 先頭 k 項を捨てる。x^k で割るイメージ
// - (f << k): 先頭に 0 を k 個足す。x^k を掛けるイメージ
//
template <class mint>
struct FormalPowerSeries : vector<mint> {
  using vector<mint>::vector;
  using FPS = FormalPowerSeries;

  // f += g
  FPS &operator+=(const FPS &r) {
    if (this->size() < r.size()) this->resize(r.size());
    for (int i = 0; i < (int)r.size(); i++) (*this)[i] += r[i];
    return *this;
  }

  // f -= g
  FPS &operator-=(const FPS &r) {
    if (this->size() < r.size()) this->resize(r.size());
    for (int i = 0; i < (int)r.size(); i++) (*this)[i] -= r[i];
    return *this;
  }

  // f *= c
  FPS &operator*=(const mint &v) {
    for (auto &x : *this) x *= v;
    return *this;
  }

  // f /= c
  FPS &operator/=(const mint &v) {
    return *this *= v.inv();
  }

  // f *= g
  // 形式的べき級数の積。多項式の畳み込みと同じ
  FPS &operator*=(const FPS &r) {
    vector<mint> res = convolution(vector<mint>(*this), vector<mint>(r));
    this->assign(res.begin(), res.end());
    return *this;
  }

  FPS operator+(const FPS &r) const { return FPS(*this) += r; }
  FPS operator-(const FPS &r) const { return FPS(*this) -= r; }
  FPS operator*(const FPS &r) const { return FPS(*this) *= r; }
  FPS operator/(const FPS &g) const { return divmod(g).first; }
  FPS operator%(const FPS &g) const { return divmod(g).second; }
  FPS operator*(const mint &v) const { return FPS(*this) *= v; }
  FPS operator/(const mint &v) const { return FPS(*this) /= v; }

  void shrink() {
    while (!this->empty() && this->back() == mint(0)) this->pop_back();
  }

  // 先頭 deg 項だけ取り出す。足りない場合は 0 埋め
  FPS pre(int deg) const {
    FPS res(this->begin(), this->begin() + min<int>(this->size(), deg));
    if ((int)res.size() < deg) res.resize(deg, mint(0));
    return res;
  }

  // 先頭 deg 項だけ取り出す。足りなくても 0 埋めしない
  FPS cut(int deg) const {
    return FPS(this->begin(), this->begin() + min<int>((int)this->size(), deg));
  }

  // 係数を反転する
  // a0 + a1 x + ... + a_{n-1} x^{n-1}
  // -> a_{n-1} + ... + a1 x^{n-2} + a0 x^{n-1}
  FPS rev(int deg = -1) const {
    FPS res(*this);
    if (deg != -1) res.resize(deg, mint(0));
    reverse(res.begin(), res.end());
    return res;
  }

  // x^k で割るイメージで先頭 k 項を落とす
  FPS operator>>(int k) const {
    if ((int)this->size() <= k) return {};
    return FPS(this->begin() + k, this->end());
  }

  // x^k を掛けるイメージで先頭に 0 を k 個足す
  FPS operator<<(int k) const {
    FPS res(k, mint(0));
    res.insert(res.end(), this->begin(), this->end());
    return res;
  }

  // 微分: a0 + a1 x + a2 x^2 + ... -> a1 + 2 a2 x + 3 a3 x^2 + ...
  FPS diff() const {
    if (this->empty()) return {};
    FPS res(max<int>(0, this->size() - 1));
    for (int i = 1; i < (int)this->size(); i++) res[i - 1] = (*this)[i] * i;
    return res;
  }

  // 積分: 積分定数は 0
  FPS integral() const {
    FPS res(this->size() + 1);
    res[0] = mint(0);
    for (int i = 0; i < (int)this->size(); i++) res[i + 1] = (*this)[i] / mint(i + 1);
    return res;
  }

  // 逆数
  // 戻り値は 1 / f mod x^deg
  // 条件: f[0] != 0
  FPS inv(int deg = -1) const {
    assert(!this->empty() && (*this)[0] != mint(0));
    if (deg == -1) deg = (int)this->size();
    FPS res{(*this)[0].inv()};
    int m = 1;
    while (m < deg) {
      m <<= 1;
      FPS f = this->cut(m);
      FPS nr = res * res * f;
      res = (res + res - nr).cut(m);
    }
    return res.pre(deg);
  }

  // 対数
  // 戻り値は log(f) mod x^deg
  // 条件: f[0] == 1
  FPS log(int deg = -1) const {
    assert(!this->empty() && (*this)[0] == mint(1));
    if (deg == -1) deg = (int)this->size();
    return (this->diff() * this->inv(deg)).pre(deg - 1).integral();
  }

  // 指数
  // 戻り値は exp(f) mod x^deg
  // 条件: f[0] == 0
  FPS exp(int deg = -1) const {
    assert(this->empty() || (*this)[0] == mint(0));
    if (deg == -1) deg = (int)this->size();
    FPS res{mint(1)};
    int m = 1;
    while (m < deg) {
      m <<= 1;
      FPS lhs = this->cut(m);
      FPS rhs = res.log(m);
      lhs -= rhs;
      lhs[0] += mint(1);
      res = (res * lhs).cut(m);
    }
    return res.pre(deg);
  }

  // べき乗
  // 戻り値は f^k mod x^deg
  // 先頭に 0 がある場合も自動で処理する
  FPS pow(long long k, int deg = -1) const {
    if (deg == -1) deg = (int)this->size();
    if (deg == 0) return {};
    if (k == 0) {
      FPS res(deg, mint(0));
      res[0] = mint(1);
      return res;
    }
    int lead = 0;
    while (lead < (int)this->size() && (*this)[lead] == mint(0)) lead++;
    if (lead == (int)this->size()) return FPS(deg, mint(0));
    if ((__int128)lead * k >= deg) return FPS(deg, mint(0));

    mint c = (*this)[lead];
    FPS g = ((*this) >> lead) / c;
    FPS res = (g.log(deg - lead * k) * mint(k)).exp(deg - lead * k) * c.pow(k);
    return (res << (lead * k)).pre(deg);
  }

  // 多項式除算
  // this = q * g + r, deg(r) < deg(g)
  // 戻り値: {q, r}
  pair<FPS, FPS> divmod(FPS g) const {
    FPS f(*this);
    f.shrink();
    g.shrink();

    assert(!g.empty());  // 0 で割ってはいけない

    if (f.size() < g.size()) {
      return {FPS{}, f};
    }

    int n = (int)f.size();
    int m = (int)g.size();
    int q_size = n - m + 1;

    // 商 Q を求める
    // f = qg + r
    // (高次を消すために反転する)
    // rev(f) = rev(q) rev(g) mod x^{q_size}
    // rev(q) = rev(f) / rev(g) mod x^{q_size}
    FPS rf = f.rev();
    FPS rg = g.rev();

    FPS q = (rf.pre(q_size) * rg.inv(q_size)).pre(q_size).rev();

    // 余り r = f - qg
    FPS r = f - q * g;

    // deg(r) < deg(g) なので、下 m-1 項だけ残す
    if ((int)r.size() > m - 1) r.resize(m - 1);
    r.shrink();

    q.shrink();
    return {q, r};
  }
};

using mint = modint998244353;
using FPS = FormalPowerSeries<mint>;

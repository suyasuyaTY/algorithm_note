# 逆元

## 逆元の存在

$f(x)$の逆元は、定数項が可逆なら存在する。

そして、次数の昇順に求められるので、必要な次数まで計算できていればいい。

[[多項式・形式的べき級数] （補足）定義や式変形の正当性の確認 | maspyのHP](https://maspypy.com/%e5%a4%9a%e9%a0%85%e5%bc%8f%e3%83%bb%e5%bd%a2%e5%bc%8f%e7%9a%84%e3%81%b9%e3%81%8d%e7%b4%9a%e6%95%b0-%ef%bc%88%e8%a3%9c%e8%b6%b3%ef%bc%89%e5%ae%9a%e7%be%a9%e3%82%84%e5%bc%8f%e5%a4%89%e5%bd%a2)

## 逆元の計算（愚直）

$$
t(x) = t_0 + t_1 x + t_2 x^2 + \cdots
$$

に対して、

$$
u(x) = u_0 + u_1 x + u_2 x^2 + \cdots
$$

が$t(x) u(x) = 1$を満たすとき、$u(x)$を$t(x)$の逆元という。

1. 定数項
    
    定数項は$t_0 u_0 = 1$となる必要があるので、$u_0 = t_0^{-1}$
    
2. それ以降
    
    $\sum_{i=0}^{n} t_i u_{n-i} = 0$となる必要があるため、
    
    $$
    u_n = t_0^{-1} \sum_{i=1}^{n} t_i u_{n-i}
    $$
    
    と計算することで順番に求めることができる。

## 逆元の計算（分割統治FFT）

$$
\begin{aligned}
f(x) &= a_0 + a_1 x + a_2 x^2 + \cdots \\
g(x) &= b_0 + b_1 x + b_2 x^2 + \cdots \\
\end{aligned}
$$

とすると、係数の比較情報から次のようになる。

$$
b_n = 
\begin{cases}
a_0^{-1} & (n = 0) \\
-a_0^{-1} \sum_{i=1}^{n} a_i b_{n-i} & (n \ge 1)
\end{cases}
$$

$c_n$を次のように定義すると

$$
c_n = 
\begin{cases}
0 & (n = 0) \\
-a_0^{-1} a_i & (n \ge 1)
\end{cases}
$$

$$
\begin{aligned}
b_n &= \sum_{i=1}^{n} c_i b_{n-1} \\
&= \sum_{i=0}^{n-1} b_i c_{n-i}
\end{aligned}
$$

```cpp
vector<mint> fps_inv(const vector<mint>& a, int N) {
  assert(!a.empty() && a[0] != 0);

  vector<mint> b(N, 0), c(N, 0);
  mint a0_inv = a[0].inv();

  b[0] = a0_inv;
  for (int i = 1; i < N; i++) {
    c[i] = -a[i] * a0_inv;
  }

  auto solve = [&](auto&& self, int l, int r) -> void {
    if (r - l == 1) return;
    int m = (l + r) / 2;

    self(self, l, m);

    vector<mint> A(b.begin() + l, b.begin() + m);
    vector<mint> B(c.begin(), c.begin() + (r - l));
    vector<mint> C = convolution(A, B);

    for (int t = m; t < r; t++) {
      if (t - l < (int)C.size()) b[t] += C[t - l];
    }

    self(self, m, r);
  };

  solve(solve, 0, N);
  return b;
}
```

## 逆元の計算（Newton法）

多項式$g_k \coloneqq g(x) \pmod{x^k}$とする（$k$次以下の係数は全て求まっているという意味）。

$$
\begin{aligned}
u_k - u_{2k} \equiv 0 \pmod{x^k}
\end{aligned}
$$

なので、

$$
\begin{aligned}
(u_k - u_{2k})^2 \equiv u_k^{2} - 2u_k u_{2k} + u_{2k}^{2} \equiv 0 \pmod{x^{2k}}
\end{aligned}
$$

となる。

ここで両辺に$t$を掛けると、$tu_{2k} \equiv 1 \pmod{x^{2k}}$となるので、

$$
\begin{aligned}
tu_k^{2} - 2u_k + u_{2k} &\equiv 0 \pmod{x^{2k}} \\
u_{2k} &\equiv 2 u_k - t u_k^2 \pmod{x^{2k}} \\
\end{aligned}
$$

となる。

```cpp
vector<mint> fps_inv(const vector<mint>& f, int deg) {
  assert(!f.empty());
  assert(f[0] != 0);

  // u_1 = 1 / f[0]
  vector<mint> g(1, f[0].inv());

  int m = 1;
  while (m < deg) {
    int need = min(2 * m, deg);

    // f の先頭 need 項だけ使えば十分
    vector<mint> f_cut(min((int)f.size(), need));
    for (int i = 0; i < (int)f_cut.size(); i++) {
      f_cut[i] = f[i];
    }

    // fg = f * g mod x^need
    vector<mint> fg = convolution(f_cut, g);
    fg.resize(need);

    // h = 2 - f*g
    vector<mint> h(need);
    h[0] = 2;
    for (int i = 0; i < need; i++) {
      h[i] -= fg[i];
    }

    // g_new = g * (2 - f*g) mod x^need
    g = convolution(g, h);
    g.resize(need);

    m = need;
  }

  return g;
}
```

<aside>

**両辺を二乗してもいい理由**

$u_k - u_{2k} \equiv 0 \pmod{x^k}$というのは、ある多項式$q(x)$があって$u_k - u_{2k} = x^{k}q(x)$と書けるという意味。

この式の両辺を二乗すると、$(u_k - u_{2k})^{2} = x^{2k}q(x)^2$となるので、$(u_k - u_{2k})^2 \equiv 0 \pmod{x^{2k}}$ となる。

</aside>

[Editorial - AtCoder Beginner Contest 260](https://atcoder.jp/contests/abc260/editorial/4434)

# 形式的冪級数

## 概要
数え上げ問題を、形式的冪級数に対する計算と結びつけることで式変形で解を得ることができる

## よく使う代数

### 二項定理
$$
(1+x)^n = \sum_{k=0}^{n} \binom{n}{k} x^k
$$

$$
(1-x)^{-n} = \sum_{k=0}^{\infty} \binom{k+n-1}{n-1} x^k
$$

### 等比級数
$$
\sum_{k=0}^{n-1} r^k = \frac{1-r^{n}}{1-r}
$$

### 形式的冪級数の計算
$ F = \sum_{n=0}^{\infty} f_n x^k, G = \sum_{n=0}^{\infty} g_n x^k$ とする。

### 和・差
$$[x^n](F \pm G) = f_n \pm g_n$$

### 積
$$[x^n](FG) = \sum_{i+j=n} f_i g_j$$

### 逆元
$F$ が定数項を持たない形式的冪級数であるとき、
$$
\frac{1}{1-F} = \sum_{n=0}^{\infty} F^{n}
$$
が成り立つ。
実際、部分和が$\frac{1 - F^N}{1-F}$となり、左辺との差は$\frac{F^N}{1-F}$ となるので、$F$に定数項がなければこの式に$N$次未満の項は存在しない。

## 形式的冪級数の性質
### 係数
$A(x) = \sum_{n = 0}^{\infty} a_n x^n$について、
$$
\begin{align*}
\sum_{n\ge 0, n: 偶数} a_n x^n &= \frac{A(x) + A(-x)}{2} \\
\sum_{n\ge 0, n: 奇数} a_n x^n &= \frac{A(x) - A(-x)}{2} \\
\end{align*}
$$

## 解法の導出

### 無限和の式変形による簡略化
等比級数の無限和などの形を利用して、$n$次の係数を導く
$$
\begin{align*}
  F &= \frac{1-x}{1-2x} \\
  &= (1-x) \cdot \frac{1}{1-2x} \\
  &= (1-x) \cdot (1 + 2x + 4x^2 + 8x^3 + \cdots) \\
\end{align*}
$$

### 因数分解の利用
> $F = (x + x^{-1} + y + y^{-1})$とするとき、$[x^a y^b] F^T$ を求めよ

$$
\begin{align*}
  F &= (xy)^{-1} (x^2 y + xy^2 + x + y) \\
  &= (xy)^{-1} (xy + 1) (x + y) \\
  F^T &= (xy)^{-T} (xy + 1)^T (x + y)^T \\
  &= (xy)^{-T} \sum_{i,j} \binom{T}{i} \binom{T}{j} (xy)^i x^{j} y^{T-j} \\
  &= \sum_{i,j} \binom{T}{i} \binom{T}{j} x^{i + j - T} y ^{i - j}
\end{align*}
$$

$i + j - T = a, i - j = b$

### 累積和によるdp遷移の導出
> $F_i = 1 + x + x^2 + \cdots + x^{a_i}$とする。$[x^K] F_1 F_2 \cdots F_N$ を計算せよ。

$F_i = \frac{1 - x^{a_i + 1}}{1 - x}$ だが、疎な多項式2つで表せている。

$$
F_i = \frac{1}{1 - x} \cdot (1 - x^{a_i + 1})
$$

ある多項式$P$に$F_i$をかける操作は、次の2つに分解できる。

1. $\frac{1}{1 - x}$ をかける
2. $(1 - x^{a_i + 1})$ をかける

**1の処理**
$P = \sum_{n = 0}^{\infty} p_n x^n, \frac{P}{1 - x} = Q = \sum_{n = 0}^{\infty} q_n x^n$ を考える。$(1 - x) Q = P$とし、$[x^n]$の部分を考えると、$n \ge 1$に対して、$q_n - q_{n-1} = p_n$ が成り立つ。そのため、次のような形で計算できる。
$$
\begin{align*}
  q_n = 
  \begin{cases}
    p_0 & \text{if $n = 0$} \\
    p_n + q_{n-1} & \text{if $n \ge 1$} \\
  \end{cases}
\end{align*}
$$

**2の処理**
$P = \sum_{n = 0}^{\infty} p_n x^n, Q = (1 - x^{a_i + 1}) P =\sum_{n = 0}^{\infty} q_n x^n$ を考える。

$$
\begin{align*}
  q_n = 
  \begin{cases}
    p_n & \text{if $n \le a_i$} \\
    p_n - p_{n - a_i - 1} & \text{if $n > a_i$} \\
  \end{cases}
\end{align*}
$$

### 戻すdpの導出
> $F_i = 1 + x + x^2 + \cdots + x^{a_i}$とする。$\Pi_{j \neq i} F_j$ の$M$次以下の係数を計算せよ。

1. $F = \Pi_{j} F_j $ を計算する
2. $\Pi_{j \neq i} F_j = \frac{F}{F_i} $ として計算する

$F$から$\frac{F}{F_i}$を得る操作は次の通り
- $(1-x)$をかける：階差数列を取る
- $(1-x^{a_i+1})$で割る：$d = a_i+1$項ごとの累積和を取る

### 分割統治FFT

FFTの形には見えるが、dpテーブルを埋めるのにdpテーブルが必要になるdpで使用

+ 分割統治なので、　$[l,m)$ を再帰的に呼び出すことで、 $[0, l)$ のテーブルを確定させることができる。
+ 計算量を削減するために、畳み込みを行う際は必要なところだけを渡す必要がある。
  + `dp`: $[l, m)$
  + `g`: $l \rightarrow r$ の遷移を確保するため $[0, min(r - l, \text{size}(g)))$. 

[分割統治FFT](https://atcoder.jp/contests/abc213/editorial/2396)

- [関連する C++ 実装](../fps/FPS.cpp)

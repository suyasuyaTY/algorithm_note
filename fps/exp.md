# exp

## 概要

$$
\exp{F(x)} = \sum_{k=0}^{\infty} \frac{F(x)^k}{k!}
$$

$F(0) = 0$とする。

$F(x)^k$の次数が少なくとも$k$になるので、固定した次数$x^n$の係数を見ると$k \le n$の有限個しか寄与しなくしたいからである。

$F(0) \neq 0$だとしたら次のように書き換えればいい。$F(x) = a_0 + \tilde{F}(x)$とすることで$\tilde{F}(0) = 0$ となる。

$$
\exp{F(x)} = \exp{(a_0 + \tilde{F}(x))} = \exp{a_0} \cdot \exp{\tilde{F}(x)}
$$

## expの求め方

$$
G(x) = \exp{F(x)}
$$

を求めたい。

ここで、すでにある段階で

$$
G_m(x) \equiv \exp{F(x)} \pmod{x^m}
$$

がわかっているとする。

$F(x)$と$\log G_m(x)$はまだずれているので、

$$
E(x) \coloneqq F(x) - \log G_m(x)
$$

と定義する。

今$G_m$は$\mod{x^m}$では正しいので、

$$
\log G_m(x) \equiv F(x) \pmod{x^m}
$$

となる。したがって、

$$
E(x) \equiv 0 \pmod{x^m}
$$

となる。ここで、

$$
\begin{aligned}
\log G(x) - \log G_m(x) &= F - \log G_m(x) = E \\
\log \frac{G(x)}{G_m(x)} &= E \\
\frac{G(x)}{G_m(x)} &= \exp{E(x)} \\
G(x) &= G_m(x) \exp{E(x)}
\end{aligned}
$$

ここで、$E(x)^2 \equiv 0 \pmod{x^{2m}}, E(x)^3 \equiv 0 \pmod{x^{3m}}$なので、

$$
\exp{E(x)} = 1 + E(x) + \frac{E(x)^2}{2!} + \cdots \equiv 1 + E \pmod{x^{2m}}
$$

$$
G(x) = G_m(x) \exp{E(x)} \equiv G_m(x) (1 + E(x)) \pmod{x^{2m}}
$$

つまり、

$$
G_{2m}(x) \coloneqq G_m(x) (1 + F - \log G_m(x)) \pmod{x^{2m}}
$$

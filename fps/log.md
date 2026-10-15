# log

## 概要

$$
\log F(x) = \int \frac{F^{\prime}(x)}{F(x)} dx
$$

で求められる。$F^{-1}(x)$が存在するために$F(0)=1$である必要がある。

## logの導出

## 微分操作

$$
F(x) = \sum_{n \ge 0} a_n x^n \Rightarrow F^\prime(x) = \sum_{n \ge 1} n a_n x^{n-1} 
$$

なので、係数をかけてからずらせばいい

## 積分操作

$$
G(x) = \sum_{n \ge 0} b_n x^n \Rightarrow \int G(x) = \sum_{n \ge 0} \frac{b_n}{n+1} x^{n+1} 
$$

$\log F(0) = \log 1 = 0$となることより、$G(0) = 0$

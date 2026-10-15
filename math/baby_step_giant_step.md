# Baby-step giant-step

## 概要

$f^{N}(x) = x$となる周期的な関数$f$に対し、$f^{t}(s) = g$となる最小の非負整数$t$を求めるアルゴリズム

## 使える条件

- $f(x)$が高速に計算できる
- $f^{M}(x)$が高速に計算できる
- 値の一致を高速に検索できる
- 逆関数$f^{-1}(x)$が存在する

## 式変形

1. $t = i M - j (1 \le i \le \lceil \frac{N}{M} \rceil, 1 \le j \le M)$という形であらわす
2. 逆関数が存在するので、$f^{iM - j}(s) = g \Leftrightarrow f^{iM}(s) = f^{j}(g)$が成り立つ

## アルゴリズム

1. 求めたい答えを$M$としたときに、$1 \le M \le U$となる$U$を探す
2. $S = \lceil \sqrt{U} \rceil$
3. $f^{1}(g), f^{2}(g), \dots, f^{S}(g)$を求め、$table[f^{k}(g)] = k$となるようにハッシュテーブルを作成する
4. $f^{iS}(s)$を求め、ハッシュテーブルと一致するものがないか検索。

## コード

[G - 222](https://atcoder.jp/contests/abc222/tasks/abc222_g)

```cpp
long long order10(long long K) {
    if (K == 1) return 1;
    if (std::gcd(10LL, K) != 1) return -1;

    // 答えは K 以下
    long long S = sqrtl(K);
    while (S * S < K) ++S;

    // 10^j を保存する
    unordered_map<long long, long long> baby;

    long long cur = 1;
    for (long long j = 0; j < S; ++j) {
        // 同じ値が複数回出たら、大きい j を残す
        baby[cur] = j;
        cur = cur * 10 % K;
    }

    long long step = mod_pow(10, S, K);  // 10^S
    long long giant = step;

    for (long long i = 1; i <= S; ++i) {
        if (baby.contains(giant)) {
            long long j = baby[giant];
            long long M = i * S - j;

            if (1 <= M && M <= K) {
                return M;
            }
        }

        giant = giant * step % K;
    }

    return -1;
}
```

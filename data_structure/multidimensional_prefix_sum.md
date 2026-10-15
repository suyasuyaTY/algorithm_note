# 多次元累積和

## ポイント

- 多次元累積和：集合の高速ゼータ変換の基数を変えたもの
- 区間クエリ：包除原理

## 多次元累積和

- 各次元について順番に1次元累積和を取る
    
    $$
    f(x_{0},\dots,x_{k},\dots, x_{d-1}) += f(x_{0},\dots,x_{k}-1,\dots, x_{d-1}) 
    $$
    
- これを全次元で行うと、最終的に`data[coord_to_idx(x)]` に次の値が入る
    
    $$
    \sum_{0 \le y_0 \le x_0} \sum_{0 \le y_1 \le x_1} \cdots \sum_{0 \le y_{d-1} \le x_{d-1}} f(y_0, \dots, y_{d-1})
    $$
    
- コードの中の変数
    - `k` ：累積和を取る次元
    - `step` ：その座標を1増減させたとき、一次減添字がいくつ変化するか
    - `block_size` ：対象の次元の値が一周する区間の長さ
    - `block` ：現在処理しているひとかたまりの開始区間
    - `offset` ：対象次元以外の添字上で変化する座標

```cpp
 // dim 次元累積和を構築する
  void build() {
    const size_t size = data.size();

    for (int k = 0; k < dim; k++) {
      // coord[k] を1増減させたときの一次元添字の差
      const size_t step = pow_base[dim - 1 - k];
      const size_t block_size = step * base;

      for (size_t block = 0; block < size; block += block_size) {
        for (size_t offset = 0; offset < step; offset++) {
          for (int digit = 1; digit < base; digit++) {
            const size_t idx =
                block + static_cast<size_t>(digit) * step + offset;

            data[idx] += data[idx - step];
          }
        }
      }
    }
  }
```

## 区間クエリ

- 各次元について、次を満たす点の総和を包除原理で求める
    
    $$
    l_{k} \le x_{k} \le r_{k}
    $$
    
- $f(S)$：集合に含まれる要素数
- $R \coloneqq \bigcap_{k=1}^{dim} (x_{k} \le r_{k})$

$$
\begin{align*}
f(R) - f \left( \bigcup_{k=1}^{dim} (l_{k} \le x_{k}) \cap R \right) &= f(R) - \sum_{k=1}^{dim} (-1)^{k-1} \sum_{J \subset |D|, |J| = k} f \left(\bigcap_{j \in J} (l_{k} \le x_{k}) \cap R \right) \\
&= \sum_{k=0}^{dim} (-1)^{k} \sum_{J \subset |D|, |J| = k} f \left(\bigcap_{j \in J} (l_{k} \le x_{k}) \cap R \right) \\
\end{align*}
$$

```cpp
 T range_sum(const Coord& lower, const Coord& upper) const {
    for (int k = 0; k < dim; k++) {
      assert(0 <= lower[k] && lower[k] < base);
      assert(0 <= upper[k] && upper[k] < base);

      if (lower[k] > upper[k]) {
        return T{};
      }
    }

    T answer{};

    const uint64_t subset_count = uint64_t{1} << dim;

    for (uint64_t mask = 0; mask < subset_count; mask++) {
      Coord corner{};

      for (int k = 0; k < dim; k++) {
        if ((mask >> k) & 1) {
          corner[k] = lower[k] - 1;
        } else {
          corner[k] = upper[k];
        }
      }

      const T value = prefix(corner);

      if (popcount(mask) % 2 == 0) {
        answer += value;
      } else {
        answer -= value;
      }
    }

    return answer;
  }
```

- [関連する C++ 実装](../data_structure/prefix_sum.cpp)

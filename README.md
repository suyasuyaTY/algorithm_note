# Algorithm Notes

AtCoder を中心とした競技プログラミングのアルゴリズムノートです。

C++ 実装は各分野のフォルダーに解説ノートと一緒に配置しています。

- 各 `.cpp` は、共通ヘッダーとして完成したものだけでなく、問題コードへ貼り付けて調整するひな形も含みます。
- `fps/FPS.cpp`、`dp/LIS.cpp`、`data_structure/segment_tree.cpp` は [AtCoder Library](https://github.com/atcoder/ac-library) に依存します。
- `ranges`、`views`、`popcount`、テンプレートの `requires` などを使う実装があるため、まとめて使う場合は C++20 を推奨します。
- `dp/LIS.cpp` には用途の異なる同名実装、`graph/euler_tour.cpp` には頂点版の重複スニペットがあります。必要な方を選んで貼り付けてください。

## データ構造

- [双対セグメント木](data_structure/dual_segment_tree.md)
- [動的セグメント木](data_structure/dynamic_segment_tree.md)
- [永続セグメント木](data_structure/persistant_segment_tree.md)
- [`segment_tree.cpp`](data_structure/segment_tree.cpp)：ACL セグメント木用の max・min・sum モノイドを定義する。`MaxMonoid`, `MinMonoid`, `SumMonoid`
- [2D Segtree](data_structure/segment_tree_2d.md)
- [`2d_segment_tree.cpp`](data_structure/2d_segment_tree.cpp)：点更新と半開矩形領域のモノイド積。`SegmentTree2D::set`, `build`, `update`, `query`
- [スパーステーブル](data_structure/sparse_table.md)
- [Disjoint Sparse Table](data_structure/disjoint_sparse_table.md)
- [平方分割](data_structure/sqrt_decomposition.md)
- [Wavelet Matrix](data_structure/wavelet_matrix.md)
- [`Wavelet_Matrix.cpp`](data_structure/Wavelet_Matrix.cpp)：部分配列の k 番目、値の出現数、前後の値を検索する。`kth_smallest`, `kth_largest`, `range_freq`, `prev_value`, `next_value`
- [区間集合の追加・削除を set で実装する](data_structure/interval_set.md)
- [スライド最大値・最小値](data_structure/sliding_window_extrema.md)
- [SWAG（Sliding Window Aggregation）](data_structure/swag.md)
- [`swag.cpp`](data_structure/swag.cpp)：キュー全体の最小値をならし O(1) で管理する。`SWAG::push`, `pop`, `fold`, `size`
- [Cartesian Tree](data_structure/cartesian_tree.md)
- [`cartesian_tree.cpp`](data_structure/cartesian_tree.cpp)：配列から最小 Cartesian Tree と各部分木の対応区間を構築する。`CartesianTree`, `CartesianTreeIntervals`
- [ヒストグラムの長方形](data_structure/histogram_rectangle.md)
- [多次元累積和](data_structure/multidimensional_prefix_sum.md)
- [`prefix_sum.cpp`](data_structure/prefix_sum.cpp)：任意次元の累積和を構築し、閉直方体領域の総和を求める。`prefix_sum<T, base, dim>`、`add`, `build`, `prefix`, `range_sum`
- [Rollback付きUnion-Find](data_structure/rollback_union_find.md)
- [`weighted_union_find.cpp`](data_structure/weighted_union_find.cpp)：頂点間のポテンシャル差を保ちながら集合を併合する。`merge`, `same`, `get_diff`, `groups`

## グラフ

- [サイクル検出](graph/cycle_detection.md)
- [`doubling.cpp`](graph/doubling.cpp)：遷移を最大 `K` 回先まで高速にたどる。`Doubling(next_nodes, max_steps)`, `query(start, steps)`
- [`functional_graph.cpp`](graph/functional_graph.cpp)：Functional Graph をサイクルまたは終端を根とする逆向きグラフへ分解する。`Functional_Graph::roots`, `G`
- [オイラー路](graph/eulerian_path.md)
- [Lowlink](graph/lowlink.md)
- [牛ゲー（最短経路問題）](graph/difference_constraints.md)
- [ポテンシャル](graph/potential.md)
- [オイラーツアー](graph/euler_tour.md)
- [`euler_tour.cpp`](graph/euler_tour.cpp)：頂点または辺に注目した Euler Tour の列を作る。問題コードへ組み込むためのひな形
- [`LCA.cpp`](graph/LCA.cpp)：Euler Tour と Sparse Table から最小共通祖先を求める。`LCA(v_tour, depth_tour, v_in)`, `query(u, v)`
- [重軽分解(HLD)](graph/heavy_light_decomposition.md)
- [`HLD.cpp`](graph/HLD.cpp)：Heavy-Light Decomposition で頂点を並べ、祖先・LCA を求める。問題コードへ組み込むためのひな形
- [重心分解](graph/centroid_decomposition.md)
- [木上のマージテク と DSU on Tree](graph/tree-small-to-large.md)

## フロー

- [最大流](flow/max_flow.md)
- [最小流量制限付き最大流](flow/lower_bound_flow.md)
- [最小費用流](flow/min_cost_flow.md)
- [燃やす埋める問題でよく使うテクニック](flow/project_selection_tricks.md)

## 動的計画法

- [最長部分増加列](dp/LIS.md)
- [`LIS.cpp`](dp/LIS.cpp)：最長増加部分列を求める。`LIS(A)`。二分探索版とセグメント木版のスニペット
- [挿入dp](dp/Insertion_dp.md)
- [耳dp](dp/phase_dp.md)
- [2 進数の下位桁から考える桁dp](dp/binary_digit_dp.md)
- [連結成分を分解するDP](dp/connected_components.md)
- [Convex Hull Trick](dp/convex_hull_trick.md)
- [Slope Trick](dp/slope_trick.md)
- [区分線形関数を imos で加算する方法](dp/piecewise_linear_imos.md)
- [凸数列の min-plus 畳み込み](dp/min_plus_convolution.md)

## オフラインアルゴリズム

- [Mo's Algorithm](offline_algorithm/mo_algorithm.md)
- [`mo_algorithm.cpp`](offline_algorithm/mo_algorithm.cpp)：オフライン区間クエリの処理順を Mo's algorithm で並べる。`Mo::add`, `build`。`solve` 内の追加・削除処理は問題ごとに実装する
- [長方形の和集合の面積](offline_algorithm/rectangle_union.md)

## 数学

- [順序論](math/order_theory.md)
- [整数論](math/number_theory.md)
- [`pow.cpp`](math/pow.cpp)：整数のべき乗と、上限を超えたら打ち切るべき乗を計算する。`powll`, `safe_pow`
- [約数の関するライブラリ](math/divisors.md)
- [`eratosthenes.cpp`](math/eratosthenes.cpp)：素数列挙、最小素因数、メビウス関数、素因数分解、約数列挙。`Eratosthenes`
- [合同方程式](math/linear_congruence.md)
- [中国剰余定理](math/chinese_remainder_theorem.md)
- [巨大な LCM を持たない合同条件の管理](math/prime_power_congruence.md)
- [Baby-step giant-step](math/baby_step_giant_step.md)
- [切り上げ、切り捨て](math/floor_ceil_division.md)
- [商の余り](math/quotient_modulo.md)
- [床関数の和（商の種類による分割）](math/floor_sum.md)
- [二重和](math/double_sum.md)
- [包除原理](math/inclusion_exclusion.md)
- [典型変形](math/combinatorial_identities.md)
- [`next_combination.cpp`](math/next_combination.cpp)：`N` 個から `K` 個を選ぶ全組合せを列挙する。`next_permutation` を使う実装例
- [多角数定理](math/polygonal_number_theorem.md)
- [浮動小数点演算における誤差によるWA回避Tips](math/floating_point.md)

## 形式的冪級数

- [形式的冪級数](fps/overview.md)
- [`FPS.cpp`](fps/FPS.cpp)：形式的べき級数の四則演算、微積分、逆数、対数、指数、べき乗を計算する。`FormalPowerSeries<mint>`。ACL の畳み込みと `modint998244353` を使用
- [NTT, Inverse NTT](fps/ntt.md)
- [逆元](fps/inverse.md)
- [log](fps/log.md)
- [exp](fps/exp.md)

## ビット演算

- [XOR の最小化・最大化](bitwise/xor_min_max.md)
- [`noshi_basis.cpp`](bitwise/noshi_basis.cpp)：複数の 64-bit 整数を一行とした XOR 線形基底を構築する。`Row<K>`, `noshi_basis(input)`
- [メビウス・ゼータ変換](bitwise/subset_transform.md)
- [アダマール変換（XOR畳み込み）](bitwise/hadamard_transform.md)

## 文字列

- [Suffix Automaton](string/suffix_automaton.md)
- [`trie_tree.cpp`](string/trie_tree.cpp)：単語の挿入、完全一致検索、接頭辞検索をする。`Trie<char_size, base>`、`insert`, `search`, `start_with`
- [`aho-corasick.cpp`](string/aho-corasick.cpp)：複数パターンをまとめたオートマトンを構築し、文字ごとに遷移する。`AhoCorasick<char_size, base>`、包含パターンの削減モード付き
- [Compressed Suffix Tree](string/compressd_suffix_tree.md)
- [文字列の辞書順とソート](string/lexicographical_order.md)
- [`rolling_hash.cpp`](string/rolling_hash.cpp)：文字列の部分区間ハッシュを O(1) で取得する。`RollingHash::get(l, r)`。2 法・乱択基数
- [括弧列](string/bracket_sequence.md)

## 幾何

- [直線](geometry/line.md)
- [凸包（Monotone Chain）](geometry/convex_hull.md)
- [点が凸図形に包含される条件](geometry/convex_containment.md)
- [距離の変換](geometry/distance_transform.md)

## ハッシュ

- [Zobrist hashing](hashing/zobrist_hashing.md)

## ゲーム

- [Nim](game/nim.md)

## C++

- [vector, ranges::views](cpp/vector_ranges.md)
- [乱数](cpp/random_and_timing.md)

## アルゴリズム

- [`binary_search.cpp`](algorithm/binary_search.cpp)：単調な判定関数に対して整数二分探索する。`my_lower_bound(L, R, check)`

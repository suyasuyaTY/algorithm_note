# SWAG（Sliding Window Aggregation）

## 概要

キューの中にある要素全体の集約値を高速に求めるデータ構造

次のような操作を全部高速にできる

- 右から要素を追加する
- 左から要素を削除する
- 今の区間全体の min / max / sum / gcd などを求める

## アルゴリズム

SWAGでは内部で`stack`を2つ使う

- `front_stack` : 左から消す用
- `back_stack`  : 右から追加する用

キュー全体は`front_stack + back_stack` になっている

1. 右に追加するときは`back_stack` に入れる
2. 左から消すときは`back_stack` から消す
3. `front_stack` が空なのに消したいときは、`back_stack` から全部移す

- [関連する C++ 実装](../data_structure/swag.cpp)

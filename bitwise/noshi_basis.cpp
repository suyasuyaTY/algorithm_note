// xor の基底
#include <algorithm>
#include <vector>

using namespace std;

using ull = unsigned long long;

template <size_t K>
struct Row {
  std::array<ull, K> a{};

  Row() = default;

  template <class... Ts>
    requires(sizeof...(Ts) == K)
  constexpr Row(Ts... xs) : a{static_cast<ull>(xs)...} {}

  constexpr ull& operator[](size_t i) {
    return a[i];
  }

  constexpr const ull& operator[](size_t i) const {
    return a[i];
  }

  constexpr bool any() const {
    for (ull x : a) {
      if (x) return true;
    }
    return false;
  }

  constexpr Row& operator^=(const Row& other) {
    for (size_t i = 0; i < K; ++i) {
      a[i] ^= other.a[i];
    }
    return *this;
  }

  friend constexpr Row operator^(Row lhs, const Row& rhs) {
    lhs ^= rhs;
    return lhs;
  }

  friend constexpr bool operator<(const Row& lhs, const Row& rhs) {
    for (size_t i = 0; i < K; ++i) {
      if (lhs.a[i] != rhs.a[i]) {
        return lhs.a[i] < rhs.a[i];
      }
    }
    return false;
  }

  friend constexpr bool operator==(const Row& lhs, const Row& rhs) {
    return lhs.a == rhs.a;
  }
};

template <size_t K>
std::vector<Row<K>> noshi_basis(const std::vector<Row<K>>& input) {
  std::vector<Row<K>> basis;

  for (auto x : input) {
    for (const auto& b : basis) {
      if ((x ^ b) < x) x ^= b;  // b の最高位 bit が x に立っていたら消す
    }
    // x は既存の基底ではもう小さくできない形になっている
    for (auto& b : basis) {
      if ((b ^ x) < b) b ^= x;  // x の最高位 bit が b に立っていたら消す
    }
    // x != 0 なら新たな基底なので追加する
    if (x.any()) basis.push_back(x);
  }

  sort(basis.begin(), basis.end());
  return basis;
}

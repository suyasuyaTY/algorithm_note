#include <atcoder/segtree>

using namespace std;

// Max monoid
namespace MaxMonoid {
using S = int;
S op(const S a, const S b) { return max(a, b); }
S e() { return 0; }  // 単位元
};  // namespace MaxMonoid

// Min monoid
namespace MinMonoid {
using S = int;
S op(const S a, const S b) { return min(a, b); }
S e() { return 0; }  // 単位元
};  // namespace MinMonoid

// sum monoid
namespace SumMonoid {
using S = int;
S op(const S a, const S b) { return a + b; }
S e() { return 0; }  // 単位元
};  // namespace SumMonoid
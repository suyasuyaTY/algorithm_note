// A = [F, F, T, T, T]: 初めてTとなる場所を返す
// L を 返すことで upper_boundにできる

template <typename F>
long long my_lower_bound(long long L, long long R, F check) {
  while (R - L > 1) {
    long long mid = (L + R) / 2;
    if (check(mid)) {
      R = mid;
    } else {
      L = mid;
    }
  }
  return R;
}
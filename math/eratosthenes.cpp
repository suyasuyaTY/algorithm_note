#include <vector>

using pii = std::pair<int, int>;

struct Eratosthenes {
  std::vector<bool> isprime;
  std::vector<int> primes;     // 素数リスト
  std::vector<int> minfactor;  // 整数 i を割り切る最小の素数
  std::vector<int> mu;         // メビウス関数

  Eratosthenes(int N) : isprime(N + 1, true), minfactor(N + 1, -1), mu(N + 1, 1) {
    isprime[1] = false;
    minfactor[1] = 1;

    for (int p = 2; p <= N; p++) {
      if (!isprime[p]) continue;

      primes.push_back(p);
      minfactor[p] = p;
      mu[p] = -1;

      for (int q = 2 * p; q <= N; q += p) {
        isprime[q] = false;
        if (minfactor[q] == -1) minfactor[q] = p;
        if ((q / p) % p == 0)
          mu[q] = 0;
        else
          mu[q] = -mu[q];
      }
    }
  }

  // 高速素因数分解 (計算量: O(log x))
  std::vector<pii> factorize(int n) const {
    std::vector<pii> res;
    while (n > 1) {
      int p = minfactor[n], ex = 0;
      while (minfactor[n] == p) {
        ex++;
        n /= p;
      }
      res.emplace_back(p, ex);
    }
    return res;
  }

  // 高速素因数分解 (計算量: O(log x))
  std::vector<int> factorize_flat(int n) const {
    std::vector<int> res;
    while (n > 1) {
      res.push_back(minfactor[n]);
      n /= minfactor[n];
    }
    return res;
  }

  // 高速約数列挙（計算量: O(\sigma(n))）
  std::vector<int> divsors(int n) {
    std::vector<int> res({1});

    auto pf = factorize(n);

    // 約数列挙
    for (auto p : pf) {
      int s = ssize(res);
      for (int i = 0; i < s; ++i) {
        int v = 1;
        for (int j = 0; j < p.second; ++j) {
          v *= p.first;
          res.push_back(res[i] * v);
        }
      }
    }
    return res;
  }
};
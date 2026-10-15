// https://drken1215.hatenablog.com/entry/2023/10/19/025800
#include <stack>
#include <vector>

using namespace std;

// 最小 Cartesian Tree の構築(a[par] <= a[child])
// - g[v]: 頂点 v の子頂点
// - root: 木の根
//

// https://nyaannyaan.github.io/library/tree/cartesian-tree.hpp.html
// return value : pair<graph, root>
template <typename T>
pair<vector<vector<int>>, int> CartesianTree(vector<T>& a) {
  int N = (int)a.size();
  vector<vector<int>> g(N);
  vector<int> p(N, -1), st;
  st.reserve(N);
  for (int i = 0; i < N; i++) {
    int prv = -1;
    while (!st.empty() && a[i] < a[st.back()]) {
      prv = st.back();
      st.pop_back();
    }
    if (prv != -1) p[prv] = i;
    if (!st.empty()) p[i] = st.back();
    st.push_back(i);
  }
  int root = -1;
  for (int i = 0; i < N; i++) {
    if (p[i] != -1)
      g[p[i]].push_back(i);
    else
      root = i;
  }
  return make_pair(g, root);
}

// Cartesian Tree における頂点 v の部分木が対応する配列上の閉区間
template <typename T>
pair<vector<int>, vector<int>> CartesianTreeIntervals(vector<T>& a) {
  int N = (int)a.size();

  if (N == 0) {
    return {{}, {}};
  }

  auto [g, root] = CartesianTree(a);

  vector<int> L(N), R(N);

  auto dfs = [&](auto self, int v) -> void {
    L[v] = R[v] = v;

    for (int child : g[v]) {
      self(self, child);
      L[v] = min(L[v], L[child]);
      R[v] = max(R[v], R[child]);
    }
  };

  dfs(dfs, root);

  return {L, R};
}
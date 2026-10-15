#include <bits/stdc++.h>

using namespace std;

void HLD() {
  int N;
  vector<vector<int>> G;

  vector<int> subtree_size(N), depth(N), parent(N);
  {
    // 1st dfs
    // calculate subtree size, put the heavy child first.
    auto dfs = [&](auto& dfs, int v, int p) -> void {
      parent[v] = p;
      depth[v] = (p == -1 ? 0 : depth[p] + 1);
      subtree_size[v] = 1;

      // 先頭に親が来ていたら一番後ろに置く
      if (!G[v].empty() && G[v][0] == p) swap(G[v][0], G[v].back());
      for (int& w : G[v]) {
        if (w == p) continue;
        dfs(dfs, w, v);
        subtree_size[v] += subtree_size[w];
        // 一番多い要素よりも多かったら一番前に置く
        if (subtree_size[w] > subtree_size[G[v][0]]) swap(G[v][0], w);
      }
    };
    dfs(dfs, 0, -1);
  }

  vector<int> vertex(N), id(N), head(N);
  {
    // 2nd dfs
    int k = 0;
    auto dfs = [&](auto& dfs, int v, int p) -> void {
      id[v] = k;
      vertex[k++] = v;
      for (int& w : G[v]) {
        if (w == p) continue;
        bool heavy = (w == G[v][0]);
        // この辺が heavy edge なら、子の head は親の head の一致
        head[w] = (heavy ? head[v] : w);
        dfs(dfs, w, v);
      }
    };
    dfs(dfs, 0, -1);
  }

  auto Level_Ancestor = [&](int v, int d) -> int {
    assert(depth[v] >= d);
    while (depth[head[v]] > d) {
      v = parent[head[v]];
    }
    return vertex[id[v] - (depth[v] - d)];
  };

  auto LCA = [&](int u, int v) -> int {
    while (head[u] != head[v]) {
      if (id[u] > id[v]) swap(u, v);
      v = parent[head[v]];
    }
    return (id[u] < id[v] ? u : v);
  };
}

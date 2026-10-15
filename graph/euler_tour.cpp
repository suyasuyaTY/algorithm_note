#include <bits/stdc++.h>

using namespace std;

void euler_tour_vertex() {
  int N;
  vector<vector<int>> G;

  vector<int> in(N), out(N), tour;
  {
    auto dfs = [&](auto &dfs, int v, int p) -> void {
      in[v] = tour.size();
      tour.push_back(v);
      for (int w : G[v]) {
        if (w == p) continue;
        dfs(dfs, w, v);
      }
      out[v] = tour.size();
    };
    dfs(dfs, 0, -1);
  }
}

void euler_tour_edge() {
  int N;

  struct Edge {
    int to, id;
  };

  vector<vector<Edge>> G;

  vector<int> in(N), out(N), tour;
  // 辺 i の子側の頂点
  // 辺 0 は根から仮想親に伸びている辺
  vector<int> e_child(N);

  {
    auto dfs = [&](auto &dfs, int v, int p) -> void {
      in[v] = tour.size();
      tour.push_back(v + 1);

      for (auto [w, edge_id] : G[v]) {
        if (w == p) continue;
        e_child[edge_id] = w;
        dfs(dfs, w, v);
      }

      out[v] = tour.size();
      tour.push_back(-(v + 1));
    };
    dfs(dfs, 0, -1);
  }
}
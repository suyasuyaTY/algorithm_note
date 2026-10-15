#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

template <int char_size, int base>
struct AhoCorasick {
  enum class ReduceMode {
    AvoidAll,   // すべて含まない: 短い語が長い語に含まれるなら、長い語を消す
    RequireAll  // すべて含む: 短い語が長い語に含まれるなら、短い語を消す
  };
  struct Node {
    array<int, char_size> nxt;  // 文字 c を追加したときの遷移先
    int fail = 0;               // 今の状態文字列の suffix のうち、パターンの prefix になっている最長のもの
    int match = -1;             // この状態で完成したパターン

    Node() {
      nxt.fill(-1);
    }
  };

  ReduceMode mode;
  vector<string> raw_patterns;
  vector<string> reduced_patterns;
  vector<Node> nodes;

  AhoCorasick(ReduceMode mode = ReduceMode::RequireAll) : mode(mode) {}

  void add(const string& s) {
    raw_patterns.push_back(s);
  }

  void add(const vector<string>& ss) {
    for (const string& s : ss) {
      add(s);
    }
  }

  pii build() {
    reduce_patterns();

    nodes.clear();
    nodes.emplace_back();  // root

    for (int i = 0; i < (int)reduced_patterns.size(); i++) {
      insert(reduced_patterns[i], i);
    }

    build_transition();

    return {
        (int)reduced_patterns.size(),
        (int)nodes.size(),
    };
  }

  int next(int state, int c) const {
    return nodes[state].nxt[c];
  }

  int next(int state, char ch) const {
    return next(state, char_id(ch));
  }

  int match_id(int state) const {
    return nodes[state].match;
  }

 private:
  static int char_id(char ch) {
    int c = ch - base;
    assert(0 <= c && c < char_size);
    return c;
  }

  void reduce_patterns() {
    reduced_patterns.clear();

    auto s = raw_patterns;

    ranges::sort(s);
    s.erase(unique(s.begin(), s.end()), s.end());

    int n = s.size();
    vector<bool> erased(n, false);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i == j) continue;
        if (s[j].find(s[i]) != string::npos) {
          if (mode == ReduceMode::AvoidAll) {
            erased[j] = true;
          } else {
            erased[i] = true;
          }
        }
      }
    }

    for (int i = 0; i < n; i++) {
      if (!erased[i]) {
        reduced_patterns.push_back(s[i]);
      }
    }
  }

  void insert(const string& s, int id) {
    int v = 0;

    for (char ch : s) {
      int c = char_id(ch);

      if (nodes[v].nxt[c] == -1) {
        nodes[v].nxt[c] = nodes.size();
        nodes.emplace_back();
      }

      v = nodes[v].nxt[c];
    }

    nodes[v].match = id;
  }

  void build_transition() {
    queue<int> q;

    for (int c = 0; c < char_size; c++) {
      int to = nodes[0].nxt[c];

      if (to == -1) {
        nodes[0].nxt[c] = 0;
      } else {
        nodes[to].fail = 0;
        q.push(to);
      }
    }

    while (!q.empty()) {
      int v = q.front();
      q.pop();

      int f = nodes[v].fail;

      for (int c = 0; c < char_size; c++) {
        int to = nodes[v].nxt[c];

        if (to == -1) {
          /*
            文字 c で直接進めないなら、
            failure 先の遷移を使う。
          */
          nodes[v].nxt[c] = nodes[f].nxt[c];
        } else {
          /*
            文字 c で直接進めるなら、
            そのノードの failure link を設定する。
          */
          nodes[to].fail = nodes[f].nxt[c];
          q.push(to);
        }
      }
    }
  }
};
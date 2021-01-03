#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using int64 = long long;

#define all($) std::begin($), std::end($)
#define rall($) std::rbegin($), std::rend($)

namespace FastIO {
class Scanner {
  char buf[1 << 19];
  char* cur = buf;

 public:
  Scanner() { fread(buf, 1, std::size(buf), stdin); }

  template <class T>
  inline Scanner& operator>>(T& val) {
    skip();
    scan(val);
    return *this;
  }

 private:
  inline void reload() {
    int res = std::distance(cur, std::end(buf));
    memcpy(buf, cur, res);
    fread(std::next(buf, res), 1, std::size(buf) - res, stdin);
    cur = buf;
  }

  inline void skip() {
    while (*cur == ' ' || *cur == '\n') ++cur;
  }

  inline void scan(int& num) {
    if (std::next(cur, 20) >= std::end(buf)) reload();
    bool neg = (*cur == '-');
    if (neg) ++cur;
    num = 0;
    while (*cur >= '0') num = num * 10 + (*cur & 15), ++cur;
    if (neg) num = -num;
  }

  inline void scan(int64& num) {
    if (std::next(cur, 20) >= std::end(buf)) reload();
    bool neg = (*cur == '-');
    if (neg) ++cur;
    num = 0;
    while (*cur >= '0') num = num * 10 + (*cur & 15), ++cur;
    if (neg) num = -num;
  }
};

class Printer {
  static constexpr int n = 10000;
  char buf[1 << 19];
  char table[n * 4];
  char* cur = buf;

 public:
  Printer() { build(); }

  ~Printer() { flush(); }

  template <class T>
  inline Printer& operator<<(T val) {
    print(val);
    return *this;
  }

  template <class T>
  inline void println(T val) {
    print(val);
    print('\n');
  }

 private:
  void build() {
    constexpr int base = 10;
    for (int i = 0; i < n; ++i) {
      int tmp = i;
      for (int j = 3; j >= 0; --j) {
        table[i * 4 + j] = tmp % base | 48;
        tmp /= base;
      }
    }
  }

  inline void flush() {
    fwrite(buf, 1, std::distance(buf, cur), stdout);
    cur = buf;
  }

  inline int get_digit(int n) {
    if (n >= (int)1e5) {
      if (n >= (int)1e8) return 9;
      if (n >= (int)1e7) return 8;
      if (n >= (int)1e6) return 7;
      return 6;
    } else {
      if (n >= (int)1e4) return 5;
      if (n >= (int)1e3) return 4;
      if (n >= (int)1e2) return 3;
      if (n >= (int)1e1) return 2;
      return 1;
    }
  }

  inline int get_digit(int64 n) {
    if (n >= (int64)1e10) {
      if (n >= (int64)1e14) {
        if (n >= (int64)1e18) return 19;
        if (n >= (int64)1e17) return 18;
        if (n >= (int64)1e16) return 17;
        if (n >= (int64)1e15) return 16;
        return 15;
      } else {
        if (n >= (int64)1e14) return 15;
        if (n >= (int64)1e13) return 14;
        if (n >= (int64)1e12) return 13;
        if (n >= (int64)1e11) return 12;
        return 11;
      }
    } else {
      if (n >= (int64)1e5) {
        if (n >= (int64)1e9) return 10;
        if (n >= (int64)1e8) return 9;
        if (n >= (int64)1e7) return 8;
        if (n >= (int64)1e6) return 7;
        return 6;
      } else {
        if (n >= (int64)1e4) return 5;
        if (n >= (int64)1e3) return 4;
        if (n >= (int64)1e2) return 3;
        if (n >= (int64)1e1) return 2;
        return 1;
      }
    }
  }

  inline void print(int num) {
    if (std::next(cur, 20) >= std::end(buf)) flush();
    if (num == 0) {
      print('0');
      return;
    }
    if (num < 0) {
      print('-');
      num = -num;
    }
    int len = get_digit(num);
    int digits = len;
    while (num >= n) {
      memcpy(cur + len - 4, table + (num % n) * 4, 4);
      num /= n;
      len -= 4;
    }
    memcpy(cur, table + num * 4 + (4 - len), len);
    cur += digits;
  }

  inline void print(int64 num) {
    if (std::next(cur, 20) >= std::end(buf)) flush();
    if (num == 0) {
      print('0');
      return;
    }
    if (num < 0) {
      print('-');
      num = -num;
    }
    int len = get_digit(num);
    int digits = len;
    while (num >= n) {
      memcpy(cur + len - 4, table + (num % n) * 4, 4);
      num /= n;
      len -= 4;
    }
    memcpy(cur, table + num * 4 + (4 - len), len);
    cur += digits;
  }

  inline void print(char c) {
    if (std::next(cur) >= std::end(buf)) flush();
    *cur = c;
    ++cur;
  }

  inline void print(const std::string& str) {
    if (std::next(cur, str.size()) >= std::end(buf)) flush();
    strcpy(cur, str.data());
    std::advance(cur, str.size());
  }

  inline void print(const char* str) {
    if (std::next(cur, std::strlen(str)) >= std::end(buf)) flush();
    strcpy(cur, str);
    std::advance(cur, std::strlen(str));
  }
};
}  // namespace FastIO

FastIO::Scanner in;
FastIO::Printer out;

int main() {
  int n; in >> n;
  using pii = pair<int, int>;
  vector<pii> edge(n - 1);
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    in >> edge[i].first >> edge[i].second;
    --edge[i].first;
    --edge[i].second;
    g[edge[i].first].emplace_back(edge[i].second);
    g[edge[i].second].emplace_back(edge[i].first);
  }

  vector<int> depth(n, -1);

  auto dfs = [&](auto&& self, int cur, int pre, int d) -> void {
    depth[cur] = d;
    for (int nxt : g[cur]) {
      if (nxt == pre) continue;
      self(self, nxt, cur, d + 1);
    }
  };

  dfs(dfs, 0, -1, 0);
  vector<int64> score(n, 0);

  constexpr int root = 0;

  int q; in >> q;
  while (q--) {
    int t, e, x; in >> t >> e >> x;
    --e;
    const auto& [a, b] = edge[e];
    if (t == 1) {
      if (depth[a] > depth[b]) {
        score[a] += x;
      } else {
        score[root] += x;
        score[b] -= x;
      }
    } else {
      if (depth[a] > depth[b]) {
        score[root] += x;
        score[a] -= x;
      } else {
        score[b] += x;
      }
    }
  }

  auto dfs2 = [&](auto&& self, int cur, int pre) -> void {
    for (int nxt : g[cur]) {
      if (nxt == pre) continue;
      score[nxt] += score[cur];
      self(self, nxt, cur);
    }
  };

  dfs2(dfs2, root, -1);

  for (int64 e : score) {
    out.println(e);
  }

  return 0;
}

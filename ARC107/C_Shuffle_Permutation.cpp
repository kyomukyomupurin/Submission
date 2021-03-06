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

template <class T>
inline int lower_position(const std::vector<T>& vec, T val) {
  return std::distance(vec.begin(),
                       std::lower_bound(vec.begin(), vec.end(), val));
}

template <class T>
inline int upper_position(const std::vector<T>& vec, T val) {
  return std::distance(vec.begin(),
                       std::upper_bound(vec.begin(), vec.end(), val));
}

template <class T>
inline std::vector<int> compressed(const std::vector<T>& vec) {
  std::vector<T> t = vec;
  std::sort(t.begin(), t.end());
  t.erase(std::unique(t.begin(), t.end()), t.end());
  std::vector<int> compressed(vec.size());
  for (size_t i = 0; i < vec.size(); ++i)
    compressed[i] =
        std::distance(t.begin(), std::lower_bound(t.begin(), t.end(), vec[i]));
  return compressed;
}

template <class T>
inline std::string to_binary(T n) {
  assert(n > 0);
  std::string ret = "";
  while (n) ret += (n & 1) ? '1' : '0', n >>= 1;
  std::reverse(ret.begin(), ret.end());
  return ret;
}

template <class T>
inline void println(T val) {
  std::cout << val << '\n';
}

inline void println(double val) {
  std::cout << std::fixed << std::setprecision(17) << val << '\n';
}

inline void println(long double val) {
  std::cout << std::fixed << std::setprecision(17) << val << '\n';
}

template <class T>
inline void println(const std::vector<T>& vec, const char del = ' ') {
  bool first = true;
  for (T e : vec) {
    if (!first) std::cout << del;
    first = false;
    std::cout << e;
  } 
  std::cout << '\n';
}

inline void Yes(bool cond) {
  println(cond ? "Yes" : "No");
}

inline void YES(bool cond) {
  println(cond ? "YES" : "NO");
}

template <class T>
using binary_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

template <class T>
std::istream& operator>>(std::istream& is, std::vector<T>& vec) {
  for (T& e : vec) is >> e;
  return is;
}

template <class T, class U>
std::istream& operator>>(std::istream& is, std::pair<T, U>& p) {
  return is >> p.first >> p.second;
}

template <class Tuple, std::size_t... Is>
void tuple_in(std::istream& is, Tuple& tp, std::index_sequence<Is...>) {
  ((is >> std::get<Is>(tp)), ...);
}

template <class... Args>
std::istream& operator>>(std::istream& is, std::tuple<Args...>& tp) {
  tuple_in(is, tp, std::index_sequence_for<Args...>{});
  return is;
}


constexpr int mod = 998244353;

class UnionFind {
 public:
  UnionFind(int n) : n_(n) { init(); }

  int root(int x) {
    assert(0 <= x && x < n_);
    if (par_[x] < 0)
      return x;
    else
      return par_[x] = root(par_[x]);
  }

  bool same(int x, int y) {
    assert(0 <= x && x < n_ && 0 <= y && y < n_);
    return root(x) == root(y);
  }

  void unite(int x, int y) {
    assert(0 <= x && x < n_ && 0 <= y && y < n_);
    x = root(x);
    y = root(y);
    if (x == y) return;
    if (par_[x] > par_[y]) std::swap(x, y);
    par_[x] += par_[y];
    par_[y] = x;
    return;
  }

  int size(int x) {
    assert(0 <= x && x < n_);
    return -par_[root(x)];
  }

 private:
  const int n_;
  std::vector<int> par_;

  void init() { par_.assign(n_, -1); }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k; cin >> n >> k;
  vector a(n, vector<int>(n)); cin >> a;

  auto Swapable_col = [&](int x, int y) -> bool {
    for (int i = 0; i < n; ++i) {
      if (a[i][x] + a[i][y] > k) return false;
    }
    return true;
  };

  auto Swapable_row = [&](int x, int y) -> bool {
    for (int i = 0; i < n; ++i) {
      if (a[x][i] + a[y][i] > k) return false;
    }
    return true;
  };

  UnionFind uf_col(n), uf_row(n);

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (Swapable_col(i, j)) uf_col.unite(i, j);
      if (Swapable_row(i, j)) uf_row.unite(i, j);
    }
  }

  vector<int64> fact(55);
  fact[1] = 1;
  for (int i = 2; i < 55; ++i) fact[i] = fact[i - 1] * i % mod;

  int64 cnt_col = 1, cnt_row = 1;
  set<int> st_row, st_col;

  for (int i = 0; i < n; ++i) st_col.emplace(uf_col.root(i));
  for (int i = 0; i < n; ++i) st_row.emplace(uf_row.root(i));

  for (int i : st_col) (cnt_col *= fact[uf_col.size(i)]) %= mod;
  for (int i : st_row) (cnt_row *= fact[uf_row.size(i)]) %= mod;

  int64 ans = cnt_col * cnt_row % mod;
  println(ans);

  return 0;
}

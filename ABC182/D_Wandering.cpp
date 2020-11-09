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

template <class T, class F>
class SparseTable {
  // F must be idempotent function!
 public:
  SparseTable(const std::vector<T>& data, F f)
      : n_((int)data.size()), lg_(32 - __builtin_clz(n_)), f_(f), data_(data) {
    build();
  }

  // return f_[l, r]
  T get(int l, int r) {
    assert(0 <= l && l <= r && r < n_);
    int lg = 32 - __builtin_clz(r - l + 1) - 1;
    return f_(tab_[lg][l], tab_[lg][r - (1 << lg) + 1]);
  }

 private:
  int n_;
  int lg_;
  F f_;
  std::vector<T> data_;
  std::vector<std::vector<T>> tab_;

  void build() {
    tab_.resize(lg_);
    tab_[0] = data_;
    for (int j = 1; j < lg_; ++j) {
      tab_[j].resize(n_ - (1 << j) + 1);
      for (int i = 0; i <= n_ - (1 << j); ++i) {
        tab_[j][i] = f_(tab_[j - 1][i], tab_[j - 1][i + (1 << (j - 1))]);
      }
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n; cin >> n;
  vector<int64> a(n); cin >> a;
  auto f = [](int64 x, int64 y){ return max(x, y); };
  vector<int64> sum(n);
  sum[0] = a[0];
  for (int i = 1; i < n; ++i) sum[i] = sum[i - 1] + a[i];
  int64 ans = 0, cur = 0;
  SparseTable st(sum, f);

  for (int i = 0; i < n; ++i) {
    ans = max(ans, cur + st.get(0, i));
    cur += sum[i];
  }

  println(ans);

  return 0;
}

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

#define all($) begin($), end($)
#define rall($) rbegin($), rend($)

template <class T>
inline void eraque(std::vector<T>& vec) {
  vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
  return;
}

template <class T>
inline int lower_position(const std::vector<T>& vec, T val) {
  return static_cast<int>(std::distance(
      vec.begin(), std::lower_bound(vec.begin(), vec.end(), val)));
}

template <class T>
inline int upper_position(const std::vector<T>& vec, T val) {
  return static_cast<int>(std::distance(
      vec.begin(), std::upper_bound(vec.begin(), vec.end(), val)));
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

template <class T>
inline void println(const std::vector<T>& vec) {
  int sz = vec.size();
  for (int i = 0; i < sz; ++i) std::cout << vec[i] << " \n"[i == sz - 1];
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

template <class M, class F>
class SegmentTree {
 public:
  SegmentTree(const std::vector<M>& data, M ie, F f)
      : ie_(ie), data_(data), f_(f) {
    build();
  }

  void update(int pos, M val) {
    assert(0 <= pos && pos < n_);
    pos += n_;
    node_[pos] = val;
    while (pos > 0) {
      pos >>= 1;
      node_[pos] = f_(node_[2 * pos], node_[2 * pos + 1]);
    }
  }

  // return f_[l, r)
  // if l >= r, return ie_
  M get(int l, int r) {
    assert(0 <= l && l < n_ && 0 <= r && r < n_ + 1);
    M vl = ie_, vr = ie_;
    for (l += n_, r += n_; l < r; l >>= 1, r >>= 1) {
      if (l & 1) vl = f_(vl, node_[l++]);
      if (r & 1) vr = f_(node_[--r], vr);
    }
    return f_(vl, vr);
  }

  M operator[](int pos) const {
    assert(0 <= pos && pos < n_);
    return node_[n_ + pos];
  }

 private:
  int n_;
  M ie_;
  std::vector<M> data_;
  std::vector<M> node_;
  F f_;

  void build() {
    int sz = data_.size();
    n_ = 1;
    while (n_ < sz) n_ <<= 1;
    node_.assign(2 * n_, ie_);
    for (int i = 0; i < sz; ++i) node_[i + n_] = data_[i];
    for (int i = n_ - 1; i > 0; --i) node_[i] = f_(node_[2 * i], node_[2 * i + 1]);
  }
};

constexpr int mod = 998244353;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k; cin >> n >> k;
  vector<pair<int, int>> pv(k); cin >> pv;

  vector<int64> dp(202020, 0);
  dp[1] = 1;

  auto f = [](int64 x, int64 y){ return (x + y) % mod; };
  vector<int64> bv(202020, 0);
  int64 ie = 0;
  SegmentTree seg(bv, ie, f);
  seg.update(1, 1);

  for (int i = 2; i <= n; ++i) {
    for (int j = 0; j < k; ++j) {
      int l = clamp(i - pv[j].second, 0, i - 1);
      int r = clamp(i - pv[j].first, 0, i - 1);
      dp[i] += seg.get(l, r + 1);
      dp[i] %= mod;
      seg.update(i, dp[i]);
    }
  }

  cout << dp[n] << endl;

  return 0;
}

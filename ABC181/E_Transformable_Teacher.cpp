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

template <class T>
class CumulativeSum {
 public:
  CumulativeSum(const std::vector<T>& vec) : vec_(vec) { build(); }

  // return sum of [l, r]
  T get(int l, int r) { return sum_[r + 1] - sum_[l]; }

  // return the first k where sum of [0, k] >= value
  // use only when all element in vec >= 0
  int lower_bound(T val) {
    return std::distance(sum_.begin() + 1,
                         std::lower_bound(sum_.begin() + 1, sum_.end(), val));
  }

  // return the first k where sum of [0, k] > value
  // use only when all element in vec >= 0
  int upper_bound(T val) {
    return std::distance(sum_.begin() + 1,
                         std::upper_bound(sum_.begin() + 1, sum_.end(), val));
  }

 private:
  std::vector<T> vec_;
  std::vector<T> sum_;

  void build() {
    sum_.resize(vec_.size() + 1);
    sum_[0] = 0;
    std::partial_sum(vec_.begin(), vec_.end(), sum_.begin() + 1);
  }
};


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m; cin >> n >> m;
  vector<int> h(n), w(m); cin >> h >> w;
  sort(all(h));
  sort(all(w));

  const int half = n / 2;
  vector<int64> forward(half), backward(half);
  for (int i = 0; i < half; ++i) forward[i] = h[i * 2 + 1] - h[i * 2];
  for (int i = 0; i < half; ++i) backward[i] = h[n - 1 - (i * 2)] - h[n - 1 - (i * 2 + 1)];

  CumulativeSum csf(forward), csb(backward);

  int64 ans = (int64)1e18;

  for (int i = 0; i < m; ++i) {
    int pos = lower_position(h, w[i]);
    int l = pos / 2, r = half - l;
    ans = min(ans, csf.get(0, l - 1) + csb.get(0, r - 1) + abs(h[l * 2] - w[i]));
  }

  println(ans);

  return 0;
}

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

inline void println(double val) {
  std::cout << std::setprecision(17) << val << '\n';
}

inline void println(long double val) {
  std::cout << std::setprecision(17) << val << '\n';
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

template <class T, class U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p) {
  return os << '(' << p.first << ", " << p.second << ')';
}

template <class Tuple, std::size_t... Is>
void tuple_out(std::ostream& os, const Tuple& tp, std::index_sequence<Is...>) {
  ((os << (Is ? ", " : "(") << std::get<Is>(tp)), ...) << ")";
}

template <class... Args>
std::ostream& operator<<(std::ostream& os, const std::tuple<Args...>& tp) {
  tuple_out(os, tp, std::index_sequence_for<Args...>{});
  return os;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
  int n = 0;
  for (auto e : vec) os << (n++ ? ", " : "{") << e;
  return os << (n ? "}" : "{}");
}

template <class T, class Compare>
std::ostream& operator<<(std::ostream& os, const std::set<T, Compare>& st) {
  int n = 0;
  for (auto e : st) os << (n++ ? ", " : "{") << e;
  return os << (n ? "}" : "{}");
}

template <class T, class U, class Compare>
std::ostream& operator<<(std::ostream& os, const std::map<T, U, Compare>& mp) {
  int n = 0;
  for (auto e : mp) os << (n++ ? ", " : "{") << e;
  return os << (n ? "}" : "{}");
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

void debug_out() { std::cerr << '\n'; }

template <class Head, class... Tail>
void debug_out(Head&& head, Tail&&... tail) {
  std::cerr << head;
  if (sizeof...(Tail) != 0) std::cerr << ", ";
  debug_out(std::forward<Tail>(tail)...);
}

constexpr int64 inf = (int64)1e18;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n; cin >> n;
  int64 k; cin >> k;
  vector<int> p(n); cin >> p;
  for (int& e : p) --e;
  vector<int64> c(n); cin >> c;

  int64 ans = -inf;

  for (int i = 0; i < n; ++i) {
    int cur = i;
    int64 sum = 0;
    vector<int64> v;
    vector<bool> used(n, false);

    while (1) {
      int nxt = p[cur];
      if (used[nxt]) break;
      used[nxt] = true;
      cur = nxt;
      sum += c[nxt];
      v.emplace_back(sum);
    }

    int64 cycle_sum = v.back();
    int64 cycle = v.size();

    if (cycle_sum >= 0) {
      if (k <= cycle) {
        for (int j = 0; j < k; ++j) ans = max(ans, v[j]);
      } else {
        int64 cnt = k / cycle;
        int64 rem = k % cycle;
        int64 t1 = *max_element(all(v));
        for (int j = 0; j < rem; ++j) ans = max(ans, cycle_sum * cnt + v[j]);
        int64 t2 = cycle_sum * (cnt - 1) + *max_element(all(v));
        ans = max({ans, t1, t2});
      }
    } else {
      if (k <= cycle) {
        for (int j = 0; j < k; ++j) ans = max(ans, v[j]);
      } else {
        ans = max(ans, *max_element(all(v)));
      }
    }
  }

  println(ans);

  return 0;
}

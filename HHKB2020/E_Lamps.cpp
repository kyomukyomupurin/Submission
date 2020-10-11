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

constexpr int mod = (int)1e9 + 7;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int h, w; cin >> h >> w;
  vector<string> sv(h); cin >> sv;

  vector dp_u(h, vector(w, 0));
  vector dp_d(h, vector(w, 0));
  vector dp_r(h, vector(w, 0));
  vector dp_l(h, vector(w, 0));

  int k = 0;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      k += (sv[i][j] == '.');
    }
  }

  for (int i = 0; i < h; ++i) {
    int cur = 0;
    for (int j = 0; j < w; ++j) {
      (sv[i][j] == '.') ? ++cur : cur = 0;
      dp_l[i][j] = cur;
    }
  }
  for (int i = 0; i < h; ++i) {
    int cur = 0;
    for (int j = w - 1; j >= 0; --j) {
      (sv[i][j] == '.') ? ++cur : cur = 0;
      dp_r[i][j] = cur;
    }
  }
  for (int i = 0; i < w; ++i) {
    int cur = 0;
    for (int j = 0; j < h; ++j) {
      (sv[j][i] == '.') ? ++cur : cur = 0;
      dp_u[j][i] = cur;
    }
  }
  for (int i = 0; i < w; ++i) {
    int cur = 0;
    for (int j = h - 1; j >= 0; --j) {
      (sv[j][i] == '.') ? ++cur : cur = 0;
      dp_d[j][i] = cur;
    }
  }

  debug(dp_d, dp_l, dp_r, dp_u);

  vector<int64> fact(4040404, 0); // fact[i] : 2^i mod 1000000007
  fact[0] = 1;
  for (int i = 1; i < 4040404; ++i) {
    fact[i] = fact[i - 1] * 2 % mod;
  }

  int64 ans = 0;

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (sv[i][j] == '.') {
        // cnt : Number of empty spaces that can light up (i, j)
        int cnt = dp_d[i][j] + dp_l[i][j] + dp_r[i][j] + dp_u[i][j] - 3;
        ans += (((fact[cnt] - 1 + mod) % mod) * fact[k - cnt] % mod);
        ans %= mod;
      }
    }
  }

  println(ans);

  return 0;
}

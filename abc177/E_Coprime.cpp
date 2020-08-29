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

int64 binary_gcd(int64 x, int64 y) {
  if (x < 0) x = -x;
  if (y < 0) y = -y;
  if (!x) return y;
  if (!y) return x;
  int s = __builtin_ctzll(x | y);
  x >>= __builtin_ctzll(x);
  do {
    y >>= __builtin_ctzll(y);
    if (x > y) std::swap(x, y);
    y -= x;
  } while (y);
  return x << s;
}

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

using int128 = __int128_t;

int128 power(int128 base, int128 e, int128 mod) {
  int128 res = 1;
  base %= mod;
  while (e) {
    if (e & 1) (res *= base) %= mod;
    (base *= base) %= mod;
    e >>= 1;
  }
  return res;
}

bool is_prime(int64 n) {
  if (n < 2 || ~n & 1) return n == 2;
  int s = __builtin_ctzll(n - 1);
  int64 d = (n - 1) >> s;
  for (int64 base : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
    int128 x = base % n;
    if (!x) continue;
    x = power(x, d, n);
    if (x == 1 || x == n - 1) continue;
    bool ok = false;
    for (int i = 0; i < s - 1; ++i) {
      (x *= x) %= n;
      if (x == n - 1) {
        ok = true; break;
      }
    }
    if (!ok) return false;
  }
  return true;
}

template <class T>
inline std::vector<T> connect(const std::vector<T> &a,
                              const std::vector<T> &b) {
  std::vector<T> c(a.size() + b.size());
  std::merge(a.begin(), a.end(), b.begin(), b.end(), c.begin());
  return c;
}

template <class T>
std::vector<T> factor(T n) {
  if (n <= 1) return {};
  if (is_prime(n)) return {n};
  if (~n & 1) return connect({2}, factor(n >> 1));
  for (T c = 1;; ++c) {
    T x = 2, y = 2, d;
    do {
      x = ((int128)x * x + c) % n;
      y = ((int128)y * y + c) % n;
      y = ((int128)y * y + c) % n;
      d = binary_gcd(x - y, n);
    } while (d == 1);
    if (d < n) return connect(factor(d), factor(n / d));
  }
}

std::vector<std::pair<char, int>> RunLengthEncoding(const std::string& str) {
  std::vector<std::pair<char, int>> ret;
  int sz = str.size();
  int beg = 0;
  while (beg < sz) {
    int ed = beg;
    while (ed + 1 < sz && str[beg] == str[ed + 1]) ++ed;
    int len = ed - beg + 1;
    ret.emplace_back(str[beg], len);
    beg = ed + 1;
  }
  return ret;
};

template <class T>
std::vector<std::pair<T, int>> RunLengthEncoding(const std::vector<T>& vec) {
  std::vector<std::pair<T, int>> ret;
  int sz = vec.size();
  int beg = 0;
  while (beg < sz) {
    int ed = beg;
    while (ed + 1 < sz && vec[beg] == vec[ed + 1]) ++ed;
    int len = ed - beg + 1;
    ret.emplace_back(vec[beg], len);
    beg = ed + 1;
  }
  return ret;
};


template <class T>
std::vector<T> divisor(T n) {
  std::vector<T> v1 = factor(n);
  auto v2 = RunLengthEncoding(v1);
  std::vector<T> div;
  int sz = v2.size();
  auto dfs = [&](auto&& self, T val, int d) -> void {
    if (d == sz) {
      div.emplace_back(val);
      return;
    }
    int cur = 1;
    auto [pr, cnt] = v2[d];
    for (int i = 0; i < cnt + 1; ++i, cur *= pr) {
      self(self, val * cur, d + 1);
    }
  };
  dfs(dfs, 1, 0);
  std::sort(div.begin(), div.end());

  return div;
}

/*
template<class T>
std::vector<T> divisor(T n) {
  std::vector<T> res;
  for (T i = 1; i * i <= n; ++i) {
    if (n % i == 0){
      res.emplace_back(i);
      if (i * i != n){
        res.emplace_back(n / i);
      }
    }
  }
  std::sort(res.begin(), res.end());

  return res;
}
*/

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n; cin >> n;
  vector<int> a(n); cin >> a;

  vector<int> cnt(1010101, 0);

  bool p_coprime = true;

  for (int i = 0; i < n; ++i) {
    vector<int> dv = divisor(a[i]);
    for (int e : dv) {
      if (e == 1) continue;
      if (cnt[e] >= 1) {
        p_coprime = false;
        break;
      }
      ++cnt[e];
    }
    if (!p_coprime) break;
  }

  if (p_coprime) {
    println("pairwise coprime");
  } else {
    int g = 0;
    for (int e : a) g = binary_gcd(g, e);
    if (g == 1) {
      println("setwise coprime");
    } else {
      println("not coprime");
    }
  }

  return 0;
}

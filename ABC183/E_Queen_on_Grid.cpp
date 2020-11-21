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

constexpr int mod = (int)1e9 + 7;
constexpr int N = 2020;

int64 dp_left[N][N];
int64 dp_above[N][N];
int64 dp_diag[N][N];

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int h, w; cin >> h >> w;
  vector<string> s(h); cin >> s;
  
  auto In = [&](int x, int y) -> bool {
    return 0 <= x && x < h && 0 <= y && y < w;
  };

  dp_left[0][0] = dp_above[0][0] = dp_diag[0][0] = 1;

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (s[i][j] == '#') continue;
      if (In(i, j - 1)) {
        if (!i && !(j - 1)) {
          dp_left[i][j] = 1; continue;
        }
        dp_left[i][j] += dp_above[i][j - 1] + dp_diag[i][j - 1];
        dp_left[i][j] += dp_left[i][j - 1] * 2;
        dp_left[i][j] %= mod;
      }
      if (In(i - 1, j)) {
        if (!(i - 1) && !j) {
          dp_above[i][j] = 1; continue;
        }
        dp_above[i][j] += dp_left[i - 1][j] + dp_diag[i - 1][j];
        dp_above[i][j] += dp_above[i - 1][j] * 2;
        dp_above[i][j] %= mod;
      }
      if (In(i - 1, j - 1)) {
        if (!(i - 1) && !(j - 1)) {
          dp_diag[i][j] = 1; continue;
        }
        dp_diag[i][j] += dp_left[i - 1][j - 1] + dp_above[i - 1][j - 1];
        dp_diag[i][j] += dp_diag[i - 1][j - 1] * 2;
        dp_diag[i][j] %= mod;
      }
    }
  }

  cout << (dp_left[h - 1][w - 1] + dp_above[h - 1][w - 1] + dp_diag[h - 1][w - 1]) % mod << endl;

  return 0;
}

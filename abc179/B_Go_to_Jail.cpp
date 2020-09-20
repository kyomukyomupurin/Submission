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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n; cin >> n;
  int cur = 0;
  bool streak = false;

  for (int i = 0; i < n; ++i) {
    int a, b; cin >> a >> b;
    if (a == b) {
      ++cur;
      if (cur == 3) {
        streak = true; break;
      }
    } else {
      cur = 0;
    }
  }

  Yes(streak);

  return 0;
}

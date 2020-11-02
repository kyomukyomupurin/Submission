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

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  string s; cin >> s;
  int n = s.size();
  if (n == 1) {
    Yes(s == "8");
  } else if (n == 2) {
    string t = s;
    reverse(all(t));
    Yes(stoi(s) % 8 == 0 || stoi(t) % 8 == 0);
  } else {
    vector<int> cnt(10, 0);
    for (char c : s) ++cnt[c - '0'];
    vector<string> sv;
    for (int i = 104; i < 1000; i += 8) {
      if (to_string(i).find('0') == string::npos) sv.emplace_back(to_string(i));
    }
    for (auto e : sv) {
      vector<int> tcnt(10, 0);
      for (char c : e) ++tcnt[c - '0'];
      bool flag = true;
      for (int i = 0; i < 10; ++i) {
        if (cnt[i] < tcnt[i]) flag = false;
      }
      if (flag) {
        Yes(1); return 0;
      }
    }
    Yes(0);
  }

  return 0;
}

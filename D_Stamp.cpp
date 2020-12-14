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
#define debug(...) std::cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define debug(...) void(0)
#endif

void debug_out() { std::cerr << '\n'; }

template <class Head, class... Tail>
void debug_out(Head&& head, Tail&&... tail) {
  std::cerr << head;
  if (sizeof...(Tail) != 0) std::cerr << ", ";
  debug_out(std::forward<Tail>(tail)...);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m; cin >> n >> m;
  vector<int> a{0};
  for (int i = 0; i < m; ++i) {
    int e; cin >> e;
    a.emplace_back(e);
  }
  a.emplace_back(n + 1);
  sort(all(a));
  debug(a);
  vector<int> dist;
  for (int i = 0; i < m + 1; ++i) {
    dist.emplace_back(a[i + 1] - a[i] - 1);
  }
  debug(dist);

  int mn = (int)1e9;
  for (int e : dist) {
    if (e) mn = min(mn, e);
  }

  int64 ans = 0;
  for (int e : dist) {
    ans += (e + mn - 1) / mn;
  }

  cout << ans << endl;

  return 0;
}

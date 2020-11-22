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

constexpr int dx[4] = {1, 0, -1, 0};
constexpr int dy[4] = {0, 1, 0, -1};

bool visited[2020][2020];

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int h, w; cin >> h >> w;
  vector<string> a(h); cin >> a;

  using pii = pair<int, int>;
  vector<vector<pii>> data(26);

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (a[i][j] >= 'a' && a[i][j] <= 'z') {
        data[a[i][j] - 'a'].emplace_back(i, j);
      }
    }
  }

  int sx, sy, gx, gy;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (a[i][j] == 'S') sx = i, sy = j;
      if (a[i][j] == 'G') gx = i, gy = j;
    }
  }

  auto In = [&](int x, int y) -> bool {
    return x >= 0 && x < h && y >= 0 && y < w;
  };

  queue<pii> que;
  que.emplace(sx, sy);
  int dist[h][w];
  constexpr int inf = (int)1e9;
  fill(dist[0], dist[h], inf);
  dist[sx][sy] = 0;
  visited[sx][sy] = true;
  set<char> used;

  while (!que.empty()) {
    auto [cx, cy] = que.front(); que.pop();
    for (int i = 0; i < 4; ++i) {
      int nx = cx + dx[i], ny = cy + dy[i];
      if (!In(nx, ny) || visited[nx][ny] || a[nx][ny] == '#') continue;
      dist[nx][ny] = dist[cx][cy] + 1;
      visited[nx][ny] = true;
      que.emplace(nx, ny);
    }
    if (a[cx][cy] >= 'a' && a[cx][cy] <= 'z') {
      if (used.find(a[cx][cy]) != used.end()) continue;
      used.emplace(a[cx][cy]);
      for (auto [tx, ty] : data[a[cx][cy] - 'a']) {
        if (visited[tx][ty]) continue;
        dist[tx][ty] = dist[cx][cy] + 1;
        visited[tx][ty] = true;
        que.emplace(tx, ty);
      }
    }
  }

  if (dist[gx][gy] == inf) {
    cout << -1 << endl;
  } else {
    cout << dist[gx][gy] << endl;
  }

  return 0;
}

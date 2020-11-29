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
class graph {
 public:
  graph(int n) : n_(n) { data_.resize(n_); }
  struct edge {
    int from, to;
    T cost;

    edge(int from_, int to_, T cost_) : from(from_), to(to_), cost(cost_) {}
  };
  int n_;
  std::vector<std::vector<int>> data_;
  std::vector<edge> edges_;

  virtual void add(int from, int to, T cost) = 0;
};

template <class T>
class forest : public graph<T> {
 public:
  using graph<T>::n_;
  using graph<T>::data_;
  using graph<T>::edges_;

  forest(int n) : graph<T>(n) {}

  void add(int from, int to, T cost = 1) {
    assert(0 <= from && from < n_ && 0 <= to && to < n_);
    int id = edges_.size();
    assert(id < n_ - 1);
    data_[from].emplace_back(id);
    data_[to].emplace_back(id);
    edges_.emplace_back(from, to, cost);
  }
};

template <class T>
class digraph : public graph<T> {
 public:
  using graph<T>::n_;
  using graph<T>::data_;
  using graph<T>::edges_;

  digraph(int n) : graph<T>(n) {}

  void add(int from, int to, T cost = 1) {
    assert(0 <= from && from < n_ && 0 <= to && to < n_);
    int id = edges_.size();
    data_[from].emplace_back(id);
    edges_.emplace_back(from, to, cost);
  }

  digraph<T> reverse() const {
    digraph<T> rev(n_);
    for (const auto& [from, to, cost] : edges_) {
      rev.add(to, from, cost);
    }
    return rev;
  }
};

template <class T>
class undigraph : public graph<T> {
 public:
  using graph<T>::n_;
  using graph<T>::data_;
  using graph<T>::edges_;

  undigraph(int n) : graph<T>(n) {}

  void add(int from, int to, T cost = 1) {
    assert(0 <= from && from < n_ && 0 <= to && to < n_);
    int id = edges_.size();
    data_[from].emplace_back(id);
    data_[to].emplace_back(id);
    edges_.emplace_back(from, to, cost);
  }
};

template <class T>
std::vector<T> dijkstra(const graph<T>& g, int s) {
  assert(0 <= s && s < g.n_);
  std::vector<T> dist(g.n_, std::numeric_limits<T>::max());
  using Pair = std::pair<T, int>;
  std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;
  dist[s] = 0;
  pq.emplace(0, s);
  while (!pq.empty()) {
    auto [d, v] = pq.top();
    pq.pop();
    if (dist[v] < d) continue;
    for (int id : g.data_[v]) {
      const auto& [from, to, cost] = g.edges_[id];
      int nxt = from ^ to ^ v;
      if (dist[nxt] > dist[v] + cost) {
        dist[nxt] = dist[v] + cost;
        pq.emplace(dist[nxt], nxt);
      }
    }
  }
  return dist;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int a, b, x, y; cin >> a >> b >> x >> y;
  --a; --b;
  undigraph<int> g(200);

  for (int i = 0; i < 100; ++i) g.add(i, i + 100, x);
  for (int i = 1; i < 100; ++i) g.add(i, i + 99, x);
  for (int i = 0; i < 99; ++i) g.add(i, i + 1, y);
  for (int i = 0; i < 99; ++i) g.add(i + 100, i + 101, y);

  auto dist = dijkstra(g, a);
  cout << dist[100 + b] << endl;

  return 0;
}

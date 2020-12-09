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

class UnionFind {
 public:
  UnionFind(int n) : n_(n) { init(); }

  int root(int x) {
    assert(0 <= x && x < n_);
    if (par_[x] < 0)
      return x;
    else
      return par_[x] = root(par_[x]);
  }

  bool same(int x, int y) {
    assert(0 <= x && x < n_ && 0 <= y && y < n_);
    return root(x) == root(y);
  }

  void unite(int x, int y) {
    assert(0 <= x && x < n_ && 0 <= y && y < n_);
    x = root(x);
    y = root(y);
    if (x == y) return;
    if (par_[x] > par_[y]) std::swap(x, y);
    par_[x] += par_[y];
    par_[y] = x;
    return;
  }

  int size(int x) {
    assert(0 <= x && x < n_);
    return -par_[root(x)];
  }

 private:
  const int n_;
  std::vector<int> par_;

  void init() { par_.assign(n_, -1); }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m; cin >> n >> m;
  UnionFind uf(n);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a; --b;
    uf.unite(a, b);
  }

  int ans = 0;
  for (int i = 0; i < n; ++i) ans = max(ans, uf.size(i));

  cout << ans << endl;

  return 0;
}

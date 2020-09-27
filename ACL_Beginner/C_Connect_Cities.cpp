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
    if (par_[x] == -1)
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
    if (rank_[x] < rank_[y]) std::swap(x, y);
    if (rank_[x] == rank_[y]) ++rank_[x];
    par_[y] = x;
    return;
  }

 private:
  const int n_;
  std::vector<int> par_;
  std::vector<int> rank_;

  void init() {
    par_.assign(n_, -1);
    rank_.assign(n_, 0);
  }
};


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m; cin >> n >> m;
  UnionFind uf(n);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b;
    --a;
    --b;
    uf.unite(a, b);
  } 

  set<int> st;
  for (int i = 0; i < n; ++i) {
    st.emplace(uf.root(i));
  }

  cout << (int)st.size() - 1 << endl;

  return 0;
}

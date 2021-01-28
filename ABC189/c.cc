#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <chrono>
#include <complex>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <tuple>

using namespace std;

using int64 = long long;

#define all($) std::begin($), std::end($)
#define rall($) std::rbegin($), std::rend($)

template <class T, class F>
class SparseTable {
  // F must be idempotent function!
 public:
  SparseTable(const std::vector<T>& data, F f)
      : n_((int)data.size()), lg_(32 - __builtin_clz(n_)), f_(f), data_(data) {
    build();
  }

  // return f_[l, r]
  T get(int l, int r) {
    assert(0 <= l && l <= r && r < n_);
    int lg = 32 - __builtin_clz(r - l + 1) - 1;
    return f_(tab_[lg][l], tab_[lg][r - (1 << lg) + 1]);
  }

 private:
  int n_;
  int lg_;
  F f_;
  std::vector<T> data_;
  std::vector<std::vector<T>> tab_;

  void build() {
    tab_.resize(lg_);
    tab_[0] = data_;
    for (int j = 1; j < lg_; ++j) {
      tab_[j].resize(n_ - (1 << j) + 1);
      for (int i = 0; i <= n_ - (1 << j); ++i) {
        tab_[j][i] = f_(tab_[j - 1][i], tab_[j - 1][i + (1 << (j - 1))]);
      }
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n; cin >> n;
  vector<int> a(n);

  for (int& e : a) cin >> e;

  int ans = -1;

  auto f = [](int x, int y){ return min(x, y); };
  SparseTable st(a, f);

  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      ans = max(ans, (j - i + 1) * st.get(i, j));
    }
  }

  cout << ans << endl;

  return 0;
}
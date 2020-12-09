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

class osa_k {
  static constexpr int n_ = 1000000 + 5;

 public:
  osa_k() { build(); }

  std::vector<std::pair<int, int>> prime_factor(int n) {
    std::vector<std::pair<int, int>> res;
    while (n != 1) {
      int p = min_factor[n];
      int cnt = 0;
      while (min_factor[n] == p) ++cnt, n /= p;
      res.emplace_back(p, cnt);
    }
    return res;
  }

 private:
  int min_factor[n_ + 1];

  void build() {
    std::fill(min_factor, min_factor + n_ + 1, 0);
    std::vector<int> pr;
    for (int i = 2; i <= n_; ++i) {
      if (!min_factor[i]) {
        min_factor[i] = i;
        pr.emplace_back(i);
      }
      for (int j = 0; j < (int)pr.size() && pr[j] <= min_factor[i] && i * pr[j] <= n_; ++j) {
        min_factor[i * pr[j]] = pr[j];
      }
    }
  }
};

osa_k os;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n; cin >> n;
  int ans = 0;

  for (int c = 1; c <= n - 1; ++c) {
    auto v = os.prime_factor(n - c);
    int sz = 1;
    for (auto e : v) {
      sz *= (e.second + 1);
    }
    ans += sz;
  }

  cout << ans << endl;

  return 0;
}

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

class Combination {
 public:
  static constexpr int mod_ = 1000000007;
  static constexpr int n_ = 20000 + 5;

  Combination() { build(); }

  int64 fact_[n_];
  int64 inv_[n_];
  int64 finv_[n_];

  // return nCk
  int64 get(int n, int k) const noexcept {
    if (n < k || n < 0 || k < 0) return 0;
    return fact_[n] * (finv_[k] * finv_[n - k] % mod_) % mod_;
  }

 private:
  void build() noexcept {
    fact_[0] = 1;
    fact_[1] = 1;
    finv_[0] = 1;
    finv_[1] = 1;
    inv_[1] = 1;
    for (int i = 2; i < n_; ++i) {
      fact_[i] = fact_[i - 1] * i % mod_;
      inv_[i] = mod_ - inv_[mod_ % i] * (mod_ / i) % mod_;
      finv_[i] = finv_[i - 1] * inv_[i] % mod_;
    }
  }
};

Combination kyomu;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int s; cin >> s;
  // s/3 個以下の区間に分ければ OK
  // k(0<=k<=s/3)個の区間に分けるとき s-s/3*k 個を k 個に配分する

  int div = s / 3;
  if (!div) {
    cout << 0 << endl; return 0;
  } else {
    int ans = 0;
    for (int i = 1; i <= div; ++i) {
      int res = s - 3 * i;
      ans += kyomu.get(res + i - 1, i - 1);
      ans %= kyomu.mod_;
    }
    cout << ans << endl;
  }

  return 0;
}

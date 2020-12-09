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
class CumulativeSum {
 public:
  CumulativeSum(const std::vector<T>& vec) : vec_(vec) { build(); }

  // return sum of [l, r]
  T get(int l, int r) { return sum_[r + 1] - sum_[l]; }

  // return the first k where sum of [0, k] >= value
  // use only when all element in vec >= 0
  int lower_bound(T val) {
    return std::distance(sum_.begin() + 1,
                         std::lower_bound(sum_.begin() + 1, sum_.end(), val));
  }

  // return the first k where sum of [0, k] > value
  // use only when all element in vec >= 0
  int upper_bound(T val) {
    return std::distance(sum_.begin() + 1,
                         std::upper_bound(sum_.begin() + 1, sum_.end(), val));
  }

 private:
  std::vector<T> vec_;
  std::vector<T> sum_;

  void build() {
    sum_.resize(vec_.size() + 1);
    sum_[0] = 0;
    std::partial_sum(vec_.begin(), vec_.end(), sum_.begin() + 1);
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int64 n; cin >> n;
  int64 x, m; cin >> x >> m;

  vector<int> pre(101010, -1);
  vector<int64> sv(101010, 0);
  int64 cur = x;

  // * * * o * * x o * * x o * * x o *
  // <---> <----->                 <-> 
  //  ini    len                   res

  for (int i = 0; i < m + 1; ++i) {
    if (i) {
      (cur *= cur) %= m;
      if (pre[cur] != -1) {
        int64 len = i - pre[cur];
        int64 ini = pre[cur];
        int64 res = (n - ini) % len;
        int64 ans = 0;
        int64 cnt = (n - ini) / len;
        CumulativeSum cs(sv);
        ans += cs.get(0, ini - 1);
        ans += cs.get(ini, ini + res - 1);
        ans += cs.get(ini, ini + len - 1) * cnt;
        cout << ans << endl; return 0;
      }
      sv[i] = cur;
      pre[cur] = i;
    } else {
      sv[i] = cur;
      pre[cur] = i;
    }
  }

  return 0;
}

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

  int n; cin >> n;
  string s; cin >> s;

  vector<int> cnt_A(n, 0);
  vector<int> cnt_T(n, 0);
  vector<int> cnt_C(n, 0);
  vector<int> cnt_G(n, 0);

  for (int i = 0; i < n; ++i) {
    cnt_A[i] += s[i] == 'A';
    cnt_T[i] += s[i] == 'T';
    cnt_C[i] += s[i] == 'C';
    cnt_G[i] += s[i] == 'G';
  }

  CumulativeSum cs_A(cnt_A);
  CumulativeSum cs_T(cnt_T);
  CumulativeSum cs_C(cnt_C);
  CumulativeSum cs_G(cnt_G);

  int ans = 0;

  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      ans += (cs_A.get(i, j) == cs_T.get(i, j) && cs_C.get(i, j) == cs_G.get(i, j));
    }
  }

  cout << ans << endl;

  return 0;
}

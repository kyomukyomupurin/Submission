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

using int128 = __int128_t;

std::istream& operator>>(std::istream& is, int128& val) {
  std::string str;
  is >> str;
  val = 0;
  bool neg = false;
  int sz = str.size();
  for (int i = 0; i < sz; ++i) {
    if (!i && str[i] == '-') {
      neg = true;
    } else {
      val = val * 10 + (str[i] & 15);
    }
  }
  if (neg) val = -val;
  return is;
}

std::ostream& operator<<(std::ostream& os, const int128& val) {
  if (!val) return os << '0';
  int128 t = val;
  if (val < 0) {
    os << '-';
    t = -t;
  }
  std::string str = "";
  while (t) {
    str += (char)(t % 10 | 48);
    t /= 10;
  }
  std::reverse(str.begin(), str.end());
  return os << str;
}

int128 to_int128(const std::string& str) {
  int sz = str.size();
  int128 val = 0;
  bool neg = false;
  for (int i = 0; i < sz; ++i) {
    if (!i && str[i] == '-') {
      neg = true;
    } else {
      val = val * 10 + (str[i] & 15);
    }
  }
  if (neg) val = -val;
  return val;
}

int128 to_int128(const char* str) {
  int128 val = 0;
  bool neg = false;
  for (int i = 0; str[i]; ++i) {
    if (!i && str[i] == '-') {
      neg = true;
    } else {
      val = val * 10 + (str[i] & 15);
    }
  }
  if (neg) val = -val;
  return val;
}

std::string to_string(const int128& val) {
  std::string str = "";
  int128 t = val;
  bool neg = false;
  if (t < 0) {
    neg = true;
    t = -t;
  }
  while (t) {
    str += (char)(t % 10 | 48);
    t /= 10;
  }
  if (neg) str += '-';
  std::reverse(str.begin(), str.end());
  return str;
}


class Combination {
 public:
  static constexpr int mod_ = 1000000007;
  static constexpr int n_ = 200000 + 5;

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

constexpr int mod = (int)1e9 + 7;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, k; cin >> n >> m >> k;
  int128 ans = 0;

  ans += (int128)(n - 1) * n * (n + 1) / 6 * m * m * kyomu.get(n * m - 2, k - 2);
  ans %= mod;
  swap(n, m);
  ans += (int128)(n - 1) * n * (n + 1) / 6 * m * m * kyomu.get(n * m - 2, k - 2);
  ans %= mod;

  cout << ans << endl;

  return 0;
}

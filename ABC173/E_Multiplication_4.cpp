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

constexpr int mod = (int)1e9 + 7;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k; cin >> n >> k;
  vector<int64> a(n);
  for (int64& e : a) cin >> e;
  if (n == k) {
    int64 ans = 1;
    for (int64 e : a) {
      ans *= e;
      ans %= mod;
      if (ans < 0) ans += mod;
    }
    cout << ans << endl;
  } else if (count(all(a), 0) > n - k) {
    cout << 0 << endl;
  } else if (all_of(all(a), [](int64 e){ return e < 0; })) {
    if (k & 1) {
      sort(rall(a));
    } else {
      sort(all(a));
    }
    int64 ans = 1;
    for (int i = 0; i < k; ++i) {
      ans *= a[i];
      ans %= mod;
      if (ans < 0) ans += mod;
    }
    cout << ans << endl;
  } else {
    // 絶対値の大きいものを貪欲に取る
    // 負の数が偶数個だったらそれでよし
    // 負の数が奇数個だったら
    // 1. 負の数のうち最も絶対値が小さいものを除いて最も絶対値の大きい正の数を追加
    // 2. 正の数のうち最も絶対値が小さいものを除いて最も絶対値の大きい負の数を追加
    // なんという苦行...
    vector<int64> pos, neg;
    copy_if(all(a), back_inserter(pos), [](int64 e){ return e >= 0; });
    copy_if(all(a), back_inserter(neg), [](int64 e){ return e < 0; });
    sort(all(pos));
    sort(rall(neg));
    vector<int64> used_pos, used_neg;
    for (int i = 0; i < k; ++i) {
      if (pos.empty()) {
        used_neg.emplace_back(neg.back());
        neg.pop_back();
      } else if (neg.empty()) {
        used_pos.emplace_back(pos.back());
        pos.pop_back();
      } else if (pos.back() > -neg.back()) {
        used_pos.emplace_back(pos.back());
        pos.pop_back();
      } else {
        used_neg.emplace_back(neg.back());
        neg.pop_back();
      }
    }
    if ((int)used_neg.size() & 1) {
      if (pos.empty() && neg.empty()) {
        ;
      } else if (pos.empty()) {
        used_pos.pop_back();
        used_neg.emplace_back(neg.back());
      } else if (neg.empty()) {
        used_neg.pop_back();
        used_pos.emplace_back(pos.back());
      } else {
        if (used_pos.empty()) {
          used_neg.pop_back();
          used_pos.emplace_back(pos.back());
        } else {
          if (pos.back() * used_pos.back() > -neg.back() * -used_neg.back()) {
          used_pos.emplace_back(pos.back());
          used_neg.pop_back();
          } else {
            used_neg.emplace_back(neg.back());
            used_pos.pop_back();
          }
        }
      }
      int64 ans = 1;
      for (int64 e : used_pos) {
        ans *= e;
        ans %= mod;
        //if (ans < 0) ans += mod;
      }
      for (int64 e : used_neg) {
        ans *= e;
        ans %= mod;
        if (ans < 0) ans += mod;
      }
      cout << ans << endl;
    } else {
      int64 ans = 1;
      for (int64 e : used_pos) {
        ans *= e;
        ans %= mod;
        //if (ans < 0) ans += mod;
      }
      for (int64 e : used_neg) {
        ans *= e;
        ans %= mod;
        if (ans < 0) ans += mod;
      }
      cout << ans << endl;
    }
  }

  return 0;
}

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

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n; cin >> n;
  using pll = pair<int64, int64>;
  vector<pll> v(n);
  for (int i = 0; i < n; ++i) cin >> v[i].first >> v[i].second;

  // a[i] * 2 + b[i]
  sort(all(v), [](const pll& x, const pll& y){
    return x.first * 2 + x.second > y.first * 2 + y.second;
  });

  int64 aoki_ini = 0;
  for (auto e : v) aoki_ini += e.first;

  for (int i = 0; i < n; ++i) {
    aoki_ini -= v[i].first * 2 + v[i].second;
    if (aoki_ini < 0) {
      cout << i + 1 << endl; return 0;
    }
  }

  return 0;
}

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
  using pii = pair<int, int>;
  vector<pii> v(n); 
  for (int i = 0; i < n; ++i) cin >> v[i].first >> v[i].second; 

  sort(rall(v));

  int cnt = 0;

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      // -1 <= (y[i] - y[j]) / (x[i] - x[j]) <= 1
      if (v[i].first - v[j].first == 0) continue;
      if (-(v[i].first - v[j].first) <= v[i].second - v[j].second && v[i].second - v[j].second <= v[i].first - v[j].first) ++cnt;
    }
  }

  cout << cnt << endl;

  return 0;
}

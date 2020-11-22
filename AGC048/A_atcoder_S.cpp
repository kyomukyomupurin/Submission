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

  int t; cin >> t;

  string atcoder = "atcoder";

  auto Solve = [&]() -> void {
    string s; cin >> s;
    string tmp = s;
    sort(rall(tmp));
    if (tmp <= atcoder) {
      cout << -1 << '\n'; return;
    }
    if (s > atcoder) {
      cout << 0 << '\n'; return;
    }
    int n = s.size();
    for (int i = 0; i < n; ++i) {
      if (s[i] != 'a') {
        if (s[i] > 't') {
          cout << i - 1 << '\n';
        } else {
          cout << i << '\n';
        }
        return;
      }
    }
  };

  while (t--) Solve();

  return 0;
}

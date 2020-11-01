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

  int n, k; cin >> n >> k;
  // a + b = K + c + d
  // a + b = X, c + d = Y
  // X = K + Y

  int64 ans = 0;

  for (int X = 2; X <= 2 * n; ++X) {
    int Y = X - k;
    if (Y >= 2 && Y <= 2 * n) {
      int64 x, y;
      if (X < n + 2) {
        x = X - 1;
      } else {
        x = X - 1 - (X % (n + 1)) * 2;
      }
      if (Y < n + 2) {
        y = Y - 1;
      } else {
        y = Y - 1 - (Y % (n + 1)) * 2;
      }
      ans += x * y;
    }
  }

  cout << ans << endl;

  return 0;
}

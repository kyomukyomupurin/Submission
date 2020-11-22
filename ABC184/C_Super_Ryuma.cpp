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

  int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
  r2 -= r1; c2 -= c1;
  r1 = c1 = 0;
  auto cond1 = [&](int a, int b, int c, int d) -> bool {
    return a + b == c + d;
  };
  auto cond2 = [&](int a, int b, int c, int d) -> bool {
    return a - b == c - d;
  };
  auto cond3 = [&](int a, int b, int c, int d) -> bool {
    return abs(a - c) + abs(b - d) <= 3;
  };

  if (r1 == r2 && c1 == c2) {
    cout << 0 << endl;
  } else if (cond1(r1, c1, r2, c2) || cond2(r1, c1, r2, c2) || cond3(r1, c1, r2, c2)) {
    cout << 1 << endl;
  } else {
    bool two = false;
    two |= abs(r1 - r2) + abs(c1 - c2) <= 6;
    int half = (abs(r2) + abs(c2)) / 2;
    int hx = half, hy = half;
    if (r2 < 0) hx = -hx;
    if (c2 < 0) hy = -hy;
    two |= cond1(r2, c2, hx, hy);
    two |= cond2(r2, c2, hx, hy);
    two |= cond3(r2, c2, hx, hy);

    if (two) {
      cout << 2 << endl;
    } else {
      cout << 3 << endl;
    }
  }

  return 0;
}

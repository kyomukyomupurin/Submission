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

  string s; cin >> s;
  int sz = s.size();

  int mn = 1728;

  for (int bit = 1; bit < (1 << sz); ++bit) {
    int t = 0;
    for (int i = 0; i < sz; ++i) {
      if ((bit >> i) & 1) {
        t += s[i] & 15;
      }
    }
    if (t % 3 == 0) mn = min(mn, sz - __builtin_popcount(bit));
  }

  if (mn == 1728) mn = -1;
  cout << mn << endl;

  return 0;
}

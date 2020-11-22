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

  int n, x; cin >> n >> x;
  string s; cin >> s;
  for (char c : s) {
    if (c == 'o') {
      ++x;
    } else {
      if (x > 0) --x;
    }
  }

  cout << x << endl;

  return 0;
}

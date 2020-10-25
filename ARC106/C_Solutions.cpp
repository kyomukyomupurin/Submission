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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m; cin >> n >> m;
  if (n == 1 && m == 0) {
    cout << 1728 << " " << 17281728 << endl;
    return 0;
  }
  if (m < 0 || m == n || m == n - 1) {
    cout << -1 << endl;
    return 0;
  }

  for (int i = 0; i < n - 1; ++i) {
    cout << 3 * (i + 1) - 1 << " " << 3 * (i + 1) << '\n'; 
  }

  cout << 1 << " " << 3 * (m + 1) + 1 << '\n';

  return 0;
}

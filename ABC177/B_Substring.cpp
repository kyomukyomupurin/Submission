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

  string s, t; cin >> s >> t;
  int n = s.size(), m = t.size();

  auto Diff = [&](const string& str) -> int {
    int need = 0;
    for (int i = 0; i < m; ++i) {
      need += str[i] != t[i];
    }
    return need;
  };

  int ans = m;

  for (int i = 0; i < n - m + 1; ++i) {
    string tmp = s.substr(i, m);
    ans = min(ans, Diff(tmp));
  }

  cout << ans << endl;

  return 0;
}

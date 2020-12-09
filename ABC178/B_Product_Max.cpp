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

  int64 a, b, c, d; cin >> a >> b >> c >> d;
  cout << max({a * c, a * d, b * c, b * d}) << endl;

  return 0;
}

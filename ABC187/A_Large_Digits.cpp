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

  string a, b; cin >> a >> b;
  int ans1 = a[0] + a[1] + a[2] - '0' * 3;
  int ans2 = b[0] + b[1] + b[2] - '0' * 3;

  cout << (int)max(ans1, ans2) << endl;

  return 0;
}

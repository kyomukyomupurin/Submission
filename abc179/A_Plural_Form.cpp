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

  string s; cin >> s;
  if (s.back() == 's') {
    cout << s << "es" << endl;
  } else {
    cout << s << "s" << endl;
  }

  return 0;
}

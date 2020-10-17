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

template<class T>
std::vector<T> divisor(T n) {
  std::vector<T> res;
  for (T i = 1; i * i <= n; ++i) {
    if (n % i == 0){
      res.emplace_back(i);
      if (i * i != n){
        res.emplace_back(n / i);
      }
    }
  }
  std::sort(res.begin(), res.end());

  return res;
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int64 n; cin >> n;
  vector<int64> v = divisor(n);
  for (int64 e : v) cout << e << '\n';

  return 0;
}

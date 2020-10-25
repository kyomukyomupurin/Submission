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

using int128 = __int128_t;

std::istream& operator>>(std::istream& is, int128& val) {
  std::string str;
  is >> str;
  val = 0;
  bool neg = false;
  int sz = str.size();
  for (int i = 0; i < sz; ++i) {
    if (!i && str[i] == '-') {
      neg = true;
    } else {
      val = val * 10 + (str[i] & 15);
    }
  }
  if (neg) val = -val;
  return is;
}

std::ostream& operator<<(std::ostream& os, const int128& val) {
  if (!val) return os << '0';
  int128 t = val;
  if (val < 0) {
    os << '-';
    t = -t;
  }
  std::string str = "";
  while (t) {
    str += (char)(t % 10 | 48);
    t /= 10;
  }
  std::reverse(str.begin(), str.end());
  return os << str;
}

int128 to_int128(const std::string& str) {
  int sz = str.size();
  int128 val = 0;
  bool neg = false;
  for (int i = 0; i < sz; ++i) {
    if (!i && str[i] == '-') {
      neg = true;
    } else {
      val = val * 10 + (str[i] & 15);
    }
  }
  if (neg) val = -val;
  return val;
}

int128 to_int128(const char* str) {
  int128 val = 0;
  bool neg = false;
  for (int i = 0; str[i]; ++i) {
    if (!i && str[i] == '-') {
      neg = true;
    } else {
      val = val * 10 + (str[i] & 15);
    }
  }
  if (neg) val = -val;
  return val;
}

std::string to_string(const int128& val) {
  std::string str = "";
  int128 t = val;
  bool neg = false;
  if (t < 0) {
    neg = true;
    t = -t;
  }
  while (t) {
    str += (char)(t % 10 | 48);
    t /= 10;
  }
  if (neg) str += '-';
  std::reverse(str.begin(), str.end());
  return str;
}

constexpr int128 MAX = (int128)1e18;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int128 n; cin >> n;
  vector<int128> v3, v5;
  int128 cur = 1;
  while (cur * 3 < MAX) {
    cur *= 3;
    v3.emplace_back(cur);
  }
  cur = 1;
  while (cur * 5 < MAX) {
    cur *= 5;
    v5.emplace_back(cur);
  }

  auto Cnt = [&](int128 num, int div) -> int {
    int cnt = 0;
    while (num != 1) {
      num /= div;
      ++cnt;
    }
    return cnt;
  };

  for (int128 e : v3) {
    int128 res = n - e;
    if (binary_search(all(v5), res)) {
      cout << Cnt(e, 3) << " " << Cnt(res, 5) << endl;
      return 0;
    }
  }

  cout << -1 << endl;

  return 0;
}

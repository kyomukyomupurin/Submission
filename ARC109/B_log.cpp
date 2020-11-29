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

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int128 n; cin >> n;
  int128 low = 1, high = n + 1;
  while (high - low > 1) {
    int128 mid = (high + low) / 2;
    if (mid * (mid + 1) > 2 * (n + 1)) {
      high = mid;
    } else {
      low = mid;
    }
  }

  cout << n - low + 1 << endl;

  return 0;
}

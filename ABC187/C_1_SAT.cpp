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

  int n; cin >> n;
  map<string, int> mp1, mp2;
  for (int i = 0; i < n; ++i) {
    string s; cin >> s;
    if (s[0] == '!') {
      s = s.substr(1);
      ++mp2[s];
    } else {
      ++mp1[s];
    }
  }

  for (const auto& [key, value] : mp1) {
    if (mp2.find(key) != mp2.end()) {
      cout << key << endl; return 0;
    }
  }

  cout << "satisfiable" << endl;

  return 0;
}

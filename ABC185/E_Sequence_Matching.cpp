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

int Levenshtein_distance(const std::vector<int>& str1, const std::vector<int>& str2) {
  int n1 = str1.size(), n2 = str2.size();
  std::vector<std::vector<int>> dp(n1 + 1, std::vector<int>(n2 + 1, 0));
  for (int i = 0; i <= n1; ++i) dp[i][0] = i;
  for (int i = 0; i <= n2; ++i) dp[0][i] = i;
  for (int i = 0; i < n1; ++i) {
    for (int j = 0; j < n2; ++j) {
      const int cost = (str1[i] != str2[j]);
      dp[i + 1][j + 1] =
          std::min({dp[i + 1][j] + 1, dp[i][j + 1] + 1, dp[i][j] + cost});
    }
  }
  return dp[n1][n2];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m; cin >> n >> m;
  vector<int> a(n), b(m);
  for (int& e : a) cin >> e;
  for (int& e : b) cin >> e;

  cout << Levenshtein_distance(a, b) << endl;

  return 0;
}

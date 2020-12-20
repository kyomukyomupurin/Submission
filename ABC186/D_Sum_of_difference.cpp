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

#include <charconv>

namespace kyomukyomuIO {
class Scanner {
  static constexpr int sz = 1 << 18;
  char buf[sz];
  char* cur = buf;

 public:
  Scanner() { fread(buf, 1, sz, stdin); }

  template <class T>
  inline Scanner& operator>>(T& val) {
    read(val);
    return *this;
  }

 private:
  inline void reload() {
    int res = sz - (cur - buf);
    memcpy(buf, cur, res);
    fread(buf + res, 1, sz - res, stdin);
    cur = buf;
  }

  inline void skip() {
    while (*cur == ' ' || *cur == '\n') ++cur;
  }

  inline void read(int& num) {
    skip();
    if (std::next(cur, 20) >= std::end(buf)) reload();
    cur = const_cast<char*>(std::from_chars(cur, std::next(cur, 20), num).ptr);
  }

  inline void read(int64& num) {
    skip();
    if (std::next(cur, 20) >= std::end(buf)) reload();
    cur = const_cast<char*>(std::from_chars(cur, std::next(cur, 20), num).ptr);
  }
};

class Printer {
  static constexpr int sz = 1 << 18;
  char buf[sz];
  char* cur = buf;

 public:
  Printer() {}

  ~Printer() { flush(); }

  template <class T>
  inline Printer& operator<<(T val) {
    write(val);
    return *this;
  }

  template <class T>
  inline void println(T val) {
    write(val);
    write('\n');
  }

 private:
  void flush() {
    fwrite(buf, 1, cur - buf, stdout);
    cur = buf;
  }

  inline void write(int num) {
    if (std::next(cur, 20) >= std::end(buf)) flush();
    cur = std::to_chars(cur, std::next(cur, 20), num).ptr;
  }

  inline void write(int64 num) {
    if (std::next(cur, 20) >= std::end(buf)) flush();
    cur = std::to_chars(cur, std::next(cur, 20), num).ptr;
  }

  inline void write(char c) {
    if (std::next(cur) >= std::end(buf)) flush();
    *cur = c;
    std::advance(cur, 1);
  }

  inline void write(const std::string& str) {
    if (std::next(cur, str.size()) >= std::end(buf)) flush();
    for (char c : str) {
      *cur = c;
      std::advance(cur, 1);
    }
  }

  inline void write(const char* str) {
    if (std::next(cur, std::strlen(str)) >= std::end(buf)) flush();
    memcpy(cur, str, std::strlen(str));
    std::advance(cur, std::strlen(str));
  }
};
}  // namespace kyomukyomuIO

kyomukyomuIO::Scanner in;
kyomukyomuIO::Printer out;

int main() {
  int n; in >> n;
  vector<int64> a(n);
  for (int64& e : a) in >> e;

  int64 sum = 0;
  int64 ans = 0;
  sort(all(a));

  for (int i = 0; i < n; ++i) {
    ans += i * a[i];
    ans -= sum;
    sum += a[i];
  }

  out.println(ans);

  return 0;
}

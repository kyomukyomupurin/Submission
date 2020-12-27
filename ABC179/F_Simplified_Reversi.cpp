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
  static constexpr int sz = 1 << 19;
  char buf[sz];
  char* cur = buf;

 public:
  Scanner() { fread(buf, 1, sz, stdin); }

  template <class T>
  inline Scanner& operator>>(T& val) {
    skip();
    scan(val);
    return *this;
  }

 private:
  inline void reload() {
    int res = std::distance(cur, std::end(buf));
    memcpy(buf, cur, res);
    fread(std::next(buf, res), 1, sz - res, stdin);
    cur = buf;
  }

  inline void skip() {
    while (*cur == ' ' || *cur == '\n') ++cur;
  }

  inline void scan(int& num) {
    if (std::next(cur, 20) >= std::end(buf)) reload();
    cur = const_cast<char*>(std::from_chars(cur, std::next(cur, 20), num).ptr);
  }

  inline void scan(int64& num) {
    if (std::next(cur, 20) >= std::end(buf)) reload();
    cur = const_cast<char*>(std::from_chars(cur, std::next(cur, 20), num).ptr);
  }
};

class Printer {
  static constexpr int sz = 1 << 19;
  char buf[sz];
  char* cur = buf;

 public:
  Printer() {}

  ~Printer() { flush(); }

  template <class T>
  inline Printer& operator<<(T val) {
    print(val);
    return *this;
  }

  template <class T>
  inline void println(T val) {
    print(val);
    print('\n');
  }

 private:
  void flush() {
    fwrite(buf, 1, std::distance(buf, cur), stdout);
    cur = buf;
  }

  inline void print(int num) {
    if (std::next(cur, 20) >= std::end(buf)) flush();
    cur = std::to_chars(cur, std::next(cur, 20), num).ptr;
  }

  inline void print(int64 num) {
    if (std::next(cur, 20) >= std::end(buf)) flush();
    cur = std::to_chars(cur, std::next(cur, 20), num).ptr;
  }

  inline void print(char c) {
    if (std::next(cur) >= std::end(buf)) flush();
    *cur = c;
    std::advance(cur, 1);
  }

  inline void print(const std::string& str) {
    if (std::next(cur, str.size()) >= std::end(buf)) flush();
    strcpy(cur, str.data());
    std::advance(cur, str.size());
  }

  inline void print(const char* str) {
    if (std::next(cur, std::strlen(str)) >= std::end(buf)) flush();
    strcpy(cur, str);
    std::advance(cur, std::strlen(str));
  }
};
}  // namespace kyomukyomuIO

kyomukyomuIO::Scanner in;
kyomukyomuIO::Printer out;


template <class OM, class F>
class DualSegmentTree {
 public:
  DualSegmentTree(const std::vector<OM>& data, OM oie, F f)
      : data_(data), oie_(oie), f_(f) {
    build();
  }

  // modify data_[l, r) -> f_(data_[l], val), ... , f_(data[r - 1], val)
  void modify(int l, int r, OM val) {
    thrust(l + n_);
    thrust(r + n_ - 1);
    for (l += n_, r += n_; l < r; l >>= 1, r >>= 1) {
      if (l & 1) lazy_[l] = f_(lazy_[l], val), ++l;
      if (r & 1) --r, lazy_[r] = f_(lazy_[r], val);
    }
  }

  OM operator[](int pos) {
    pos += n_;
    thrust(pos);
    return f_(data_[pos - n_], lazy_[pos]);
  }

 private:
  int n_, h_;
  std::vector<OM> data_;
  std::vector<OM> lazy_;
  F f_;
  OM oie_;

  void build() {
    int sz = data_.size();
    n_ = 1;
    h_ = 0;
    while (n_ < sz) n_ <<= 1, ++h_;
    lazy_.assign(2 * n_, oie_);
  }

  inline void propagate(int pos) {
    if (lazy_[pos] != oie_) {
      lazy_[2 * pos + 0] = f_(lazy_[2 * pos + 0], lazy_[pos]);
      lazy_[2 * pos + 1] = f_(lazy_[2 * pos + 1], lazy_[pos]);
      lazy_[pos] = oie_;
    }
  }

  inline void thrust(int pos) {
    for (int i = h_; i > 0; --i) propagate(pos >> i);
  }
};

int main() {
  int n, q; in >> n >> q;
  auto f = [](int x, int y) { return min(x, y); };
  vector<int> bv(n + 1, n);
  DualSegmentTree col(bv, n - 1, f); // col[i] : i 列目で最初に黒が現れる位置
  DualSegmentTree row(bv, n - 1, f); // row[i] : i 行目で最初に黒が現れる位置

  int64 ans = (int64)(n - 2) * (n - 2);

  while (q--) {
    int t, x; in >> t >> x;
    if (t == 1) { // (1, x)
      int pos = col[x];
      ans -= pos - 1;
      row.modify(2, pos + 1, x - 1);
    } else { // (x, 1)
      int pos = row[x];
      ans -= pos - 1;
      col.modify(2, pos + 1, x - 1);
    }
  }

  out.println(ans);

  return 0;
}

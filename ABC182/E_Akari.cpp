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

namespace FastIO {
class Scanner {
  static constexpr int buf_size = (1 << 18);
  static constexpr int integer_size = 20;
  static constexpr int string_size = 1000; // the maximum possible size of input string
  char buf[buf_size] = {};
  char *cur = buf, *ed = buf;

 public:
  Scanner() {}

  template <class T>
  inline Scanner& operator>>(T& val) {
    read(val);
    return *this;
  }

 private:

  // TO DO : memmove -> memcpy
  inline void reload() {
    size_t len = ed - cur;
    memmove(buf, cur, len);
    char* tmp = buf + len;
    ed = tmp + fread(tmp, 1, buf_size - len, stdin);
    *ed = 0;
    cur = buf;
  }

  inline void skip_space() {
    while (true) {
      if (cur == ed) reload();
      while (*cur == ' ' || *cur == '\n') ++cur;
      if (__builtin_expect(cur != ed, 1)) return;
    }
  }

  template <class T, std::enable_if_t<std::is_same<T, int>::value, int> = 0>
  inline void read(T& num) {
    skip_space();
    if (cur + integer_size >= ed) reload();
    bool neg = false;
    num = 0;
    if (*cur == '-') neg = true, ++cur;
    while (*cur >= '0') num = num * 10 + (*cur & 15), ++cur;
    if (neg) num = -num;
  }

  template <class T, std::enable_if_t<std::is_same<T, int64>::value, int> = 0>
  inline void read(T& num) {
    skip_space();
    if (cur + integer_size >= ed) reload();
    bool neg = false;
    num = 0;
    if (*cur == '-') neg = true, ++cur;
    while (*cur >= '0') num = num * 10 + (*cur & 15), ++cur;
    if (neg) num = -num;
  }

  template <class T,
            std::enable_if_t<std::is_same<T, std::string>::value, int> = 0>
  inline void read(T& str) {
    skip_space();
    if (cur + str.size() >= ed) reload();
    auto it = cur;
    while (!(*cur == ' ' || *cur == '\n')) ++cur;
    str = std::string(it, cur);
  }

  template <class T, std::enable_if_t<std::is_same<T, char>::value, int> = 0>
  inline void read(T& c) {
    skip_space();
    if (cur + 1 >= ed) reload();
    c = *cur, ++cur;
  }

  template <class T, std::enable_if_t<std::is_same<T, double>::value, int> = 0>
  inline void read(T& num) {
    skip_space();
    if (cur + integer_size >= ed) reload();
    bool neg = false;
    num = 0;
    if (*cur == '-') neg = true, ++cur;
    while (*cur >= '0' && *cur <= '9') num = num * 10 + (*cur & 15), ++cur;
    if (*cur != '.') return;
    ++cur;
    T base = 0.1;
    while (*cur >= '0' && *cur <= '9') {
      num += base * (*cur ^ 48);
      ++cur;
      base *= 0.1;
    }
    if (neg) num = -num;
  }

  template <class T,
            std::enable_if_t<std::is_same<T, long double>::value, int> = 0>
  inline void read(T& num) {
    skip_space();
    if (cur + integer_size >= ed) reload();
    bool neg = false;
    num = 0;
    if (*cur == '-') neg = true, ++cur;
    while (*cur >= '0' && *cur <= '9') num = num * 10 + (*cur & 15), ++cur;
    if (*cur != '.') return;
    ++cur;
    T base = 0.1;
    while (*cur >= '0' && *cur <= '9') {
      num += base * (*cur ^ 48);
      ++cur;
      base *= 0.1;
    }
    if (neg) num = -num;
  }

  template <class T>
  inline void read(std::vector<T>& vec) {
    for (T& e : vec) read(e);
  }

  template <class T, class U>
  inline void read(std::pair<T, U>& p) {
    read(p.first, p.second);
  }

  template <class Tuple, std::size_t... Is>
  inline void tuple_scan(Tuple& tp, std::index_sequence<Is...>) {
    (read(std::get<Is>(tp)), ...);
  }

  template <class... Args>
  inline void read(std::tuple<Args...>& tp) {
    tuple_scan(tp, std::index_sequence_for<Args...>{});
  }

  inline void read() {}

  template <class Head, class... Tail>
  inline void read(Head&& head, Tail&&... tail) {
    read(head);
    read(std::forward<Tail>(tail)...);
  }
};

class Printer {
  static constexpr int buf_size = (1 << 18);
  static constexpr int integer_size = 20;
  static constexpr int string_size = (1 << 6);
  static constexpr int margin = 1;
  static constexpr int n = 10000;
  char buf[buf_size + margin] = {};
  char table[n * 4] = {};
  char* cur = buf;

 public:
  Printer() { build(); }

  ~Printer() { flush(); }

  template <class T>
  inline Printer& operator<<(T val) {
    write(val);
    return *this;
  }

  template<class T>
  inline void println(T val) {
    write(val);
    write('\n');
  }

 private:
  void build() {
    constexpr int base = 10;
    for (int i = 0; i < n; ++i) {
      int tmp = i;
      for (int j = 3; j >= 0; --j) {
        table[i * 4 + j] = tmp % base | 48;
        tmp /= base;
      }
    }
  }

  inline void flush() {
    fwrite(buf, 1, cur - buf, stdout);
    cur = buf;
  }

  template <class T, std::enable_if_t<std::is_same<T, int>::value, int> = 0>
  inline int get_digit(T n) {
    if (n >= (int)1e5) {
      if (n >= (int)1e8) return 9;
      if (n >= (int)1e7) return 8;
      if (n >= (int)1e6) return 7;
      return 6;
    } else {
      if (n >= (int)1e4) return 5;
      if (n >= (int)1e3) return 4;
      if (n >= (int)1e2) return 3;
      if (n >= (int)1e1) return 2;
      return 1;
    }
  }

  template <class T, std::enable_if_t<std::is_same<T, int64>::value, int> = 0>
  inline int get_digit(T n) {
    if (n >= (int64)1e10) {
      if (n >= (int64)1e14) {
        if (n >= (int64)1e18) return 19;
        if (n >= (int64)1e17) return 18;
        if (n >= (int64)1e16) return 17;
        if (n >= (int64)1e15) return 16;
        return 15;
      } else {
        if (n >= (int64)1e14) return 15;
        if (n >= (int64)1e13) return 14;
        if (n >= (int64)1e12) return 13;
        if (n >= (int64)1e11) return 12;
        return 11;
      }
    } else {
      if (n >= (int64)1e5) {
        if (n >= (int64)1e9) return 10;
        if (n >= (int64)1e8) return 9;
        if (n >= (int64)1e7) return 8;
        if (n >= (int64)1e6) return 7;
        return 6;
      } else {
        if (n >= (int64)1e4) return 5;
        if (n >= (int64)1e3) return 4;
        if (n >= (int64)1e2) return 3;
        if (n >= (int64)1e1) return 2;
        return 1;
      }
    }
  }

  template <class T, std::enable_if_t<std::is_same<T, int>::value, int> = 0>
  inline void write(T num) {
    if (__builtin_expect(cur + integer_size >= buf + buf_size, 0)) flush();
    if (num == 0) {
      write('0');
      return;
    }
    if (num < 0) {
      write('-');
      num = -num;
    }
    int len = get_digit(num);
    int digits = len;
    while (num >= n) {
      memcpy(cur + len - 4, table + (num % n) * 4, 4);
      num /= n;
      len -= 4;
    }
    memcpy(cur, table + num * 4 + (4 - len), len);
    cur += digits;
  }

  template <class T, std::enable_if_t<std::is_same<T, int64>::value, int> = 0>
  inline void write(T num) {
    if (__builtin_expect(cur + integer_size >= buf + buf_size, 0)) flush();
    if (num == 0) {
      write('0');
      return;
    }
    if (num < 0) {
      write('-');
      num = -num;
    }
    int len = get_digit(num);
    int digits = len;
    while (num >= n) {
      memcpy(cur + len - 4, table + (num % n) * 4, 4);
      num /= n;
      len -= 4;
    }
    memcpy(cur, table + num * 4 + (4 - len), len);
    cur += digits;
  }

  template <class T, std::enable_if_t<std::is_same<T, char>::value, int> = 0>
  inline void write(T c) {
    if (__builtin_expect(cur + 1 >= buf + buf_size, 0)) flush();
    *cur = c;
    ++cur;
  }

  template <class T,
            std::enable_if_t<std::is_same<T, std::string>::value, int> = 0>
  inline void write(T str) {
    if (__builtin_expect(cur + str.size() >= buf + buf_size, 0)) flush();
    for (char c : str) write(c);
  }

  template <class T,
            std::enable_if_t<std::is_same<T, const char*>::value, int> = 0>
  inline void write(T str) {
    if (__builtin_expect(cur + string_size >= buf + buf_size, 0)) flush();
    for (int i = 0; str[i]; ++i) write(str[i]);
  }
};
}  // namespace FastIO

FastIO::Scanner fin;
FastIO::Printer fout;

bool light[1515][1515];
bool bulb[1515][1515];
bool block[1515][1515];

int main() {
  // std::ios_base::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  int h, w; fin >> h >> w;
  int n, m; fin >> n >> m;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) {
    fin >> a[i] >> b[i];
    --a[i], --b[i];
    bulb[a[i]][b[i]] = true;
    light[a[i]][b[i]] = true;
  }
  vector<int> c(m), d(m);
  for (int i = 0; i < m; ++i) {
    fin >> c[i] >> d[i];
    --c[i], --d[i];
    block[c[i]][d[i]] = true;
  }

  auto LightUp = [&](int i, int j) -> void {
    while (i - 1 >= 0) {
      --i;
      if (bulb[i][j] || block[i][j]) return;
      light[i][j] = true;
    }
  };

  auto LightDown = [&](int i, int j) -> void {
    while (i + 1 < h) {
      ++i;
      if (bulb[i][j] || block[i][j]) return;
      light[i][j] = true;
    }
  };

  auto LightLeft = [&](int i, int j) -> void {
    while (j - 1 >= 0) {
      --j;
      if (bulb[i][j] || block[i][j]) return;
      light[i][j] = true;
    }
  };

  auto LightRight = [&](int i, int j) -> void {
    while (j + 1 < w) {
      ++j;
      if (bulb[i][j] || block[i][j]) return;
      light[i][j] = true;
    }
  };

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (bulb[i][j]) {
        LightUp(i, j);
        LightDown(i, j);
        LightLeft(i, j);
        LightRight(i, j);
      }
    }
  }

  int ans = 0;

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      ans += light[i][j];
    }
  }

  // cout << ans << endl;
  fout.println(ans);

  return 0;
}

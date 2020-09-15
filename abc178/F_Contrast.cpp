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

template <class T>
inline void eraque(std::vector<T>& vec) {
  vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
  return;
}

template <class T>
inline int lower_position(const std::vector<T>& vec, T val) {
  return static_cast<int>(std::distance(
      vec.begin(), std::lower_bound(vec.begin(), vec.end(), val)));
}

template <class T>
inline int upper_position(const std::vector<T>& vec, T val) {
  return static_cast<int>(std::distance(
      vec.begin(), std::upper_bound(vec.begin(), vec.end(), val)));
}

template <class T>
inline std::string to_binary(T n) {
  assert(n > 0);
  std::string ret = "";
  while (n) ret += (n & 1) ? '1' : '0', n >>= 1;
  std::reverse(ret.begin(), ret.end());
  return ret;
}

template <class T>
inline void println(T val) {
  std::cout << val << '\n';
}

template <class T>
inline void println(const std::vector<T>& vec) {
  int sz = vec.size();
  for (int i = 0; i < sz; ++i) std::cout << vec[i] << " \n"[i == sz - 1];
}

inline void Yes(bool cond) {
  println(cond ? "Yes" : "No");
}

inline void YES(bool cond) {
  println(cond ? "YES" : "NO");
}

template <class T>
using binary_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

template <class T>
std::istream& operator>>(std::istream& is, std::vector<T>& vec) {
  for (T& e : vec) is >> e;
  return is;
}

template <class T, class U>
std::istream& operator>>(std::istream& is, std::pair<T, U>& p) {
  return is >> p.first >> p.second;
}

template <class Tuple, std::size_t... Is>
void tuple_in(std::istream& is, Tuple& tp, std::index_sequence<Is...>) {
  ((is >> std::get<Is>(tp)), ...);
}

template <class... Args>
std::istream& operator>>(std::istream& is, std::tuple<Args...>& tp) {
  tuple_in(is, tp, std::index_sequence_for<Args...>{});
  return is;
}

class Timer {
 public:
  // (second)
  double get_elapsed_time() {
    return static_cast<double>(get_cycle() - start_) /
           static_cast<double>(clock_frequency_);
  }

  void start() { start_ = get_cycle(); }

 private:
  int64_t start_;
  //static constexpr int64_t clock_frequency_ = 1800000000; // Local
  static constexpr int64_t clock_frequency_ = 3000000000; // AtCoder
  //static constexpr int64_t clock_frequency_ = 3600000000; // Codeforces
  //static constexpr int64_t clock_frequency_ = 2300000000; // yukicoder

  int64_t get_cycle() {
    uint32_t low, high;
    __asm__ volatile("rdtsc" : "=a"(low), "=d"(high));
    return (static_cast<int64_t>(low)) | (static_cast<int64_t>(high) << 32);
  }
};

// This is xoroshiro128+ 1.0
// Reference : http://prng.di.unimi.it/xoroshiro128plus.c
class Xoroshiro {
 public:
  Xoroshiro() {
    s[0] = static_cast<uint64_t>(std::chrono::steady_clock::now().time_since_epoch().count());
    s[1] = s[0] ^ 0xffffffffful;
    for (int i = 0; i < (1 << 6); ++i) next();
  }

  using result_type = uint64_t;
  static constexpr uint64_t min() { return std::numeric_limits<result_type>::min(); }
  static constexpr uint64_t max() { return std::numeric_limits<result_type>::max(); }

  uint64_t operator()() { return next(); }

 private:
  uint64_t s[2];

  static inline uint64_t rotl(const uint64_t x, int k) {
    return (x << k) | (x >> (64 - k));
  }

  uint64_t next() {
    const uint64_t s0 = s[0];
    uint64_t s1 = s[1];
    const uint64_t result = s0 + s1;
    s1 ^= s0;
    s[0] = rotl(s0, 24) ^ s1 ^ (s1 << 16);
    s[1] = rotl(s1, 37);

    return result;
  }
};


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  Timer time;
  time.start();

  Xoroshiro rng;

  int n; cin >> n;
  vector<int> a(n), b(n); cin >> a >> b;

  vector<int> cnt_a(202020, 0), cnt_b(202020);
  for (int e : a) ++cnt_a[e];
  for (int e : b) ++cnt_b[e];
  for (int i = 0; i < 202020; ++i) {
    if (cnt_a[i] + cnt_b[i] > n) {
      Yes(0); return 0;
    }
  }

  Yes(1);

  uniform_int_distribution<int> dist(0, n - 1);

  // B を reverse してから、a[i] = b[i] になってるところを見つけたらランダムに
  // swap して解消する。これを時間いっぱいやる
  // これで通ったけど、いいのか？！
  // B の全要素を走査する毎に終了条件のチェックを入れたらめっちゃ速くなった

  reverse(all(b));

  auto Finish = [&]() -> bool {
    for (int i = 0; i < n; ++i) {
      if (a[i] == b[i]) return false;
    }
    return true;
  };

  while (true) {
    if (Finish()) {
      println(b); return 0;
    }
    for (int i = 0; i < n; ++i) {
      if (time.get_elapsed_time() > 1.9) {
        println(b); return 0;
      }
      if (a[i] == b[i]) {
        int cur = a[i];
        int p = i;
        while (b[p] == cur) {
          p = dist(rng);
          if (time.get_elapsed_time() > 1.9) {
            println(b); return 0;
          }
        }
        swap(b[i], b[p]);
        if (time.get_elapsed_time() > 1.9) {
          println(b); return 0;
        }
      }
    }
  }

  return 0;
}

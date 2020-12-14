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

template <class M, class F>
class SegmentTree {
 public:
  SegmentTree(const std::vector<M>& data, M ie, F f)
      : ie_(ie), data_(data), f_(f) {
    build();
  }

  void update(int pos, M val) {
    assert(0 <= pos && pos < n_);
    pos += n_;
    node_[pos] = val;
    while (pos > 0) {
      pos >>= 1;
      node_[pos] = f_(node_[2 * pos], node_[2 * pos + 1]);
    }
  }

  // return f_[l, r)
  // if l >= r, return ie_
  M get(int l, int r) {
    assert(0 <= l && l < n_ && 0 <= r && r < n_ + 1);
    M vl = ie_, vr = ie_;
    for (l += n_, r += n_; l < r; l >>= 1, r >>= 1) {
      if (l & 1) vl = f_(vl, node_[l++]);
      if (r & 1) vr = f_(node_[--r], vr);
    }
    return f_(vl, vr);
  }

  M operator[](int pos) const {
    assert(0 <= pos && pos < n_);
    return node_[n_ + pos];
  }

  // return f_[0, sz_)
  M get_all() { return node_[1]; }

  // return the maximum i that satisfies cond(i) == true, where i >= l
  // if there is no such i, return sz_
  template <class Condition>
  int max_right(int l, Condition cond) {
    assert(0 <= l && l <= sz_);
    assert(cond(ie_));
    if (l == sz_) return sz_;
    l += n_;
    M sm = ie_;

    do {
      while (~l & 1) l >>= 1;
      if (!cond(f_(sm, node_[l]))) {
        while (l < n_) {
          l <<= 1;
          if (cond(f_(sm, node_[l]))) {
            sm = f_(sm, node_[l]);
            ++l;
          }
        }
        return l - n_;
      }
      sm = f_(sm, node_[l]);
      ++l;
    } while ((l & -l) != l);

    return sz_;
  }

  // return the minimum i that satisfies cond(i) == true, where i <= r
  // if there is no such i, return 0
  // NOT VERIFIED!!
  template <class Condition>
  int min_left(int r, Condition cond) {
    assert(0 <= r && r <= sz_);
    assert(cond(ie_));
    if (r == 0) return 0;
    r += n_;
    M sm = ie_;

    do {
      --r;
      while (r > 1 && (r & 1)) r >>= 1;
      if (!cond(f_(node_[r], sm))) {
        while (r < n_) {
          r = (2 * r + 1);
          if (cond(f_(node_[r], sm))) {
            sm = f_(node_[r], sm);
            --r;
          }
        }
        return r + 1 - n_;
      }
      sm = f_(node_[r], sm);
    } while ((r & -r) != r);

    return 0;
  }

 private:
  int n_;
  int sz_;
  M ie_;
  std::vector<M> data_;
  std::vector<M> node_;
  F f_;

  void build() {
    sz_ = data_.size();
    n_ = 1;
    while (n_ < sz_) n_ <<= 1;
    node_.assign(2 * n_, ie_);
    for (int i = 0; i < sz_; ++i) node_[i + n_] = data_[i];
    for (int i = n_ - 1; i > 0; --i) node_[i] = f_(node_[2 * i], node_[2 * i + 1]);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q; cin >> n >> q;
  vector<int64> a(n);
  for (auto& e : a) cin >> e;

  auto f = [](int64 x, int64 y){ return x ^ y; };
  constexpr int64 ie = 0;
  SegmentTree seg(a, ie, f);

  while (q--) {
    int t; cin >> t;
    if (t == 1) {
      int x; int64 y; cin >> x >> y;
      int64 cur = seg[x - 1];
      seg.update(x - 1, f(cur, y));
    } else {
      int x, y; cin >> x >> y;
      cout << seg.get(x - 1, y) << '\n';
    }
  }

  return 0;
}

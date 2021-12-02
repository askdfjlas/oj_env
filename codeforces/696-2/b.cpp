#include <bits/stdc++.h>
using namespace std;
// https://space.bilibili.com/672328094
#define ll long long
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  constexpr ll N = 2e5;
  vector<int> min_primes(N + 1), primes;
  primes.reserve(1e5);
  for (int i = 2; i <= N; i++) {
    if (!min_primes[i]) min_primes[i] = i, primes.push_back(i);
    for (auto& p : primes) {
      if (i * p > N) break;
      min_primes[i * p] = p;
      if (i % p == 0) break;
    }
  }
  int T, n;
  cin >> T;
  while (T--) {
    cin >> n;
    ll p1 = *upper_bound(primes.begin(), primes.end(), n);
    ll p2 = *lower_bound(primes.begin(), primes.end(), p1 + n);
    // cout << p1 << " " << p2 << endl;
    cout << p1 * p2 << '\n';
  }
}
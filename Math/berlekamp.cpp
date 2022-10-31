/*BerlekampMassey.h
Description: Recovers any n-order linear recurrence relation from the first
2n terms of the recurrence. Useful for guessing linear recurrences after brute-
forcing the first terms. Should work on any field, but numerical stability for
floats is not guaranteed. Output will have size ≤ n.
Usage: berlekampMassey({0, 1, 1, 3, 5, 11}) // {1, 2}
Time: O (N 2 )*/
vector<ll> berlekampMassey(vector<ll> s) {
  int n = sz(s), L = 0, m = 0;
  vector<ll> C(n), B(n), T;
  C[0] = B[0] = 1;
  ll b = 1;
  fore(i,0,n) { ++m;
  ll d = s[i] % mod;
  fore(j,1,L+1) d = (d + C[j] * s[i - j]) % mod;
  if (!d) continue;
  T = C; ll coef = d * modpow(b, mod-2) % mod;
  fore(j,m,n) C[j] = (C[j] - coef * B[j - m]) % mod;
  if (2 * L > i) continue;
  L = i + 1 - L; B = T; b = d; m = 0;
  }
  C.resize(L + 1); C.erase(C.begin());
  for (ll& x : C) x = (mod - x) % mod;
  return C;
}

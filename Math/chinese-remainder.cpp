constexpr ll safe_mod(ll x, ll m) {
  x %= m; if (x < 0) x += m; return x; }
constexpr std::pair<ll, ll> inv_gcd(ll a, ll b) {
  a = safe_mod(a, b); if (a == 0) return {b, 0};
  ll s = b, t = a, m0 = 0, m1 = 1;
  while (t) {
  ll u = s / t; s -= t * u; m0 -= m1 * u; ll tmp = s;
  s = t; t = tmp; tmp = m0; m0 = m1; m1 = tmp; }
  if (m0 < 0) m0 += b / s; return {s, m0}; }
ii crt(vi& r, const vi& m) {
  assert(r.size()==m.size());int n=int(r.size()); ll r0=0,m0=1;
  for (int i = 0; i < n; i++) {
  assert(1 <= m[i]); ll r1=safe_mod(r[i], m[i]), m1 = m[i];
  if (m0 < m1) { swap(r0, r1); swap(m0, m1); }
  if (m0%m1==0) { if (r0%m1!=r1) return {0,0}; continue; }
  ll g, im; tie(g, im) = inv_gcd(m0, m1); ll u1 = (m1 / g);
  if ((r1 - r0) % g) return {0, 0};
  ll x = (r1 - r0) / g % u1 * im % u1; r0 += x * m0; m0 *= u1;
  if (r0 < 0) r0 += m0; } return {r0, m0}; }
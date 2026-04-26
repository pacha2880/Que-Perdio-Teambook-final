vi prime; bool iscom[MAXN];
void sieve (int n) { fill(iscom, iscom + n, false);
  for (int i = 2; i < n; ++i) {
    if (!iscom[i]) prime.push_back (i);
    for (int j = 0; j < prime.size () && i*prime[j] < n; ++j) {
      iscom[i*prime[j]] = true; if (i%prime[j]==0) break; } } }
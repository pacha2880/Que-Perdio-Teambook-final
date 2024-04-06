for (int i = 0; i < n; ++i) {
  // increasing: lower_bound; non-decreasing: upper_bound
  int j = lower_bound(dp, dp + lis, v[i]) - dp;
  dp[j] = min(dp[j], v[i]); lis = max(lis, j + 1); }
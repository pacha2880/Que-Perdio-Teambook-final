fore(sz, 0, n) {
  for (int i = 0; i + sz < n; i++) {
  int j = i+sz;
  // CASOS BASE
  if (sz <= 1) { // Barra inexistente o con cero cortes en medio
    DP[i][j] = 0;
    continue;
  }
  if (sz == 2) { // Barra con un solo corte posible en medio
    K[i][j] = i+1;
    DP[i][j] = C[i][j];
    continue;
  }
  int KL = K[i][j-1];
  int KR = K[i+1][j];
  DP[i][j] = INF;
  for (int k = KL; k <= KR; k++) {
    int newVal = DP[i][k] + DP[k][j] + C[i][j];
    if (newVal < DP[i][j]) {
    K[i][j] = k;
    DP[i][j] = newVal;
    }
  }
  }
}

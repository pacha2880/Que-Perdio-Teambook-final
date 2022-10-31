// Catalan, parentesis balanceados, arboles binarios, triangulacion poligono convexto de n + 2 lados, caminos en grilla sin atravesar diagonal
// Cat[n] = C(2n, n) / (n + 1)
// C(n, k) es el coeficiente binomial
Cat[0] = 1;
Cat[n+1] = Cat[n] * 2 * (2 * n + 1) / (n + 2);
Cat[n] = Cat[n-1] * 2 * (2 * n - 1) / (n + 1);
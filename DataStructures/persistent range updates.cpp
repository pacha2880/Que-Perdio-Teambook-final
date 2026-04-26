bool hasflag[]; int flag[];
int newlazykid(int node, int delta, int L, int R);
void propagate(int p, int L, int R) {if (hasflag[p]) {
    if (L != R) {
      l[p] = newlazykid(l[p], flag[p], L, M);
      r[p] = newlazykid(r[p], flag[p], M + 1, R);}
    hasflag[p] = false;}}
int newlazykid(int node, int delta, int L, int R) {
  int p = ++NODES;l[p] = l[node];r[p]=r[node];flag[p]=flag[node];
  hasflag[p] = true;flag[p] += delta;
  st[p] = st[node] + (R - L + 1) * delta;return p;}
int update(int a, int b, int x, int p, int L=0, int R=n-1) {
  if (b < L || R < a)   return p;
  if (a <= L && R <= b) return newlazykid(p, x, L, R); 
  propagate(p, L, R);
  return newparent(update(a, b, l[p], x, L, M),
           update(a, b, r[p], x, M + 1, R));}
int query(int a, int b, int p, int L=0, int R=n-1) {
  if (b < L || R < a)   return 0;
  if (a <= L && R <= b) return st[p];
  propagate(p, L, R);
  return query(a, b, l[p], x, L, M) + query(a b,r[p],x,M+1,R);}
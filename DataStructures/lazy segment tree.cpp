
int ar[tam], t[4 * tam], l[4 * tam];
void push(int b, int e, int node) {
  if(l[node]) {
    t[node] += l[node];
    if(b < e)
      l[node * 2 + 1] += l[node], l[node * 2 + 2] += l[node];
    l[node] = 0; } }
void update(int b, int e, int node, int i, int j, int val) {
  if(b > e) return; push(b, e, node);
  if(e < i || b > j) return;
  if(b >= i && e <= j) {
    l[node] += val; push(b, e, node); return; }
  index; update(b, mid, l, i, j, val);
  update(mid + 1, e, r, i, j, val);
  t[node] = max(t[l], t[r]); }
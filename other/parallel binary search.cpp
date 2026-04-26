struct Query { int i, ans; /*+ query related info*/ };
vector<Query> req;
void pbs(vector<Query>& qs,int l/*=minv*/,int r/*=maxv*/) {
  if (qs.empty()) return;
  if (l==r) { for(auto&q:qs)req[q.i].ans=l;return; }
  int mid = (l + r) / 2;
  //mid = (l + r + 1) / 2 if different simple upper/lower bound
  for (int i = l; i <= mid; i++) { /*add val to ds*/ }
  vector<Query> vl, vr; for (auto& q : qs) {
    if (/* cond */) vl.push_back(q); else vr.push_back(q); }
  pbs(vr, mid + 1, r);
  for (int i = l; i <= mid; i++) { /*remove val from ds*/ }
  pbs(vl, l, mid); }
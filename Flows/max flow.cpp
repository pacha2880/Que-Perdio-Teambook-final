struct Dinitz{
  const int INF = 1e9 + 7; Dinitz(){}
  Dinitz(int n, int s, int t) {init(n, s, t);}
  void init(int n, int s, int t) {
    S = s, T = t; nodes = n;
    G.clear(), G.resize(n); Q.resize(n); }
  struct flowEdge { int to, rev, f, cap; };
  vector<vector<flowEdge> > G;
  void addEdge(int st, int en, int cap) {
    flowEdge A = {en, (int)G[en].size(), 0, cap};
    flowEdge B = {st, (int)G[st].size(), 0, 0};
    G[st].pb(A); G[en].pb(B); }
  int nodes, S, T; vi work, lvl, Q;
  bool bfs() {
    int qt = 0; Q[qt++] = S;
    lvl.assign(nodes, -1); lvl[S] = 0;
    for (int qh = 0; qh < qt; qh++) {
      int v = Q[qh];
      for (flowEdge &e : G[v]) {
        int u = e.to;
        if (e.cap <= e.f || lvl[u] != -1) continue;
        lvl[u] = lvl[v] + 1; Q[qt++] = u; } }
    return lvl[T] != -1; }
  int dfs(int v, int f) {
    if (v == T || f == 0) return f;
    for (int &i = work[v]; i < G[v].size(); i++) {
      flowEdge &e = G[v][i]; int u = e.to;
      if (e.cap <= e.f || lvl[u] != lvl[v] + 1) continue;
      int df = dfs(u, min(f, e.cap - e.f));
      if (df) {
        e.f += df; G[u][e.rev].f -= df; return df; } }
    return 0; }
  int maxFlow() {
    int flow = 0;
    while (bfs()) {
      work.assign(nodes, 0);
      while (true) {
        int df = dfs(S, INF); if (df == 0) break;
        flow += df; } }
    return flow; }
};
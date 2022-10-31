namespace dinic { // can someone please test_me >_<
  int s, t;
  int gp[110][110], usados[110], lev[110];
  vi g[110];
  bool bfs(int maxscal)  {
    int node;queue<int> que;
    memset(lev,-1,sizeof(lev));
    que.push(s); lev[s]=0;
    while(!que.empty()) {
      node = que.front();que.pop();
      for(int i=0;i<g[node].size();i++) {
        if(lev[g[node][i]]==-1 && gp[node][g[node][i]] >= maxscal) {
          que.push(g[node][i]); lev[g[node][i]]= lev[node] + 1;
        }               }
    }   return lev[t]!=-1;
  }
  int dfs(int node, int f) {
    if(node==t) return f;
    for(;usados[node]<g[node].size();usados[node]++) {
      int u = g[node][usados[node]];
      if(lev[u]!=lev[node]+1 || gp[node][u] < f ) continue;
      int flow = dfs(u,min(gp[node][u],f));
      if(flow>0) {
        gp[node][u]-=flow; gp[u][node]+=flow;return flow;
      }                       }
    return 0;
  }
  int maxFlow() {
    int flujo=0,ax;
    for(int scaling=30;scaling>=0;scaling--) { //pragma? O(VElogF)
      while(bfs(1<<scaling)) {
        memset(usados,0,sizeof(usados));
        while(true) {
          ax=dfs(s,1<<scaling);
          if (ax == 0) break;
          flujo+=ax;
        }
      }
    }
  }
}   //with scaling
/*  without scaling
 *  bool bfs()
 *  if(lev[g[node][i]]==-1 && gp[node][g[node][i]]>0)
 *  if(lev[u]!=lev[node]+1 || gp[node][u] <= 0 ) continue;
 *  while(bfs())
 *  ax=dfs(s,INT_MAX);
 * */

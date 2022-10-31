bool try_kuhn(int v) { // O(nm) tested)
    if (used[v])
        return false;
    used[v] = true;
    for (int to : g[v]) {
        if (mt[to] == -1 || try_kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}
void doit(){ mt.assign(k, -1);
    fore(v,0,n){
        used.assign(n, false);
        try_kuhn(v);
    }
//fore(i,0,k) if (mt[i] != -1)cout<<mt[i]+1<<' '<<i+1<<'\n';
}

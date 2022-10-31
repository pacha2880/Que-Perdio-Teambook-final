class MaxFlow{ // tested:)
private:
    map<int,int> g[K];
    bool vis[K];ii prnt[K];int I,F;
public:
    void Addedge(int i,int j,int flowin) {
        g[i][j]+= flowin;
        g[j][i];//unidirectional
    }
    int dfs(int u, int flow) {
        vis[u] = 1;
        bool ans = 0;
        if (u == F)
            return 1;
        for(auto& par: g[u]) {
            int i = par.fi, flowin = par.se;
            if (vis[i] || flowin < flow)continue;
            bool axd = dfs(i,flow);
            if (axd) 
                prnt[u] = par;
            ans |= axd;
        }
        return ans;
    }
    void update(int w, int flow) {
        while(w != F)   { 
            auto parz = prnt[w];
            int z = parz.fi; // w->z
            auto it1 = g[z].lower_bound(w);auto p1 = (*it1);
            auto it2 = g[w].lower_bound(z);auto p2 = (*it2);
            assert(it1 != g[z].end());
            assert(it2 != g[w].end());
            g[z].erase(it1);
            g[w].erase(it2);
            p1.se += flow;
            p2.se -= flow;
            g[z].insert(p1);
            g[w].insert(p2);
            w = z;      }
    }
    int GetFlow(int II,int FF) {
        I = II;
        F = FF;
        ll tot = 0; // O(EV log F ) (log E map?)
        for(int pot =17; pot>=0; pot--) {
            memset(vis,0,sizeof vis);
            while (dfs(I, 1ll<<pot)) {
                tot += (1<<pot);
                update(I, 1<<pot);
                memset(vis,0,sizeof vis);
            }           }
        return tot;            }
    };

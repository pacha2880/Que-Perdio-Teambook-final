//Polynomial division: O(n*log(n))
//Multi-point polynomial evaluation: O(n*log^2(n))
//Polynomial interpolation: O(n*log^2(n))
//Works with NTT. For FFT, replace addmod,submod,mulmod,inv
poly add(poly &a, poly &b){
  int n=sz(a),m=sz(b);poly ans(max(n,m));fore(i,0,max(n,m)){
    if(i<n) ans[i]=addmod(ans[i],a[i]);
    if(i<m) ans[i]=addmod(ans[i],b[i]); }
  while(sz(ans)>1&&!ans.back())ans.pop_back(); return ans; }
poly invert(poly &b, int d){
  poly c = {inv(b[0])};
  while(sz(c)<=d){int j=2*sz(c); auto bb=b; bb.resize(j);
    poly cb=multiply(c,bb);
    fore(i,0,sz(cb)) cb[i]=submod(0,cb[i]); cb[0]=addmod(cb[0],2);
    c=multiply(c,cb); c.resize(j);}c.resize(d+1); return c; }
pair<poly,poly> divslow(poly &a, poly &b){poly q,r=a;
  while(sz(r)>=sz(b)){ q.pb(mulmod(r.back(),inv(b.back())));
    if(q.back()) fore(i,0,sz(b)){
      r[sz(r)-i-1]=submod(r[sz(r)-i-1],mulmod(q.back(),b[sz(b)-i-1])); }
    r.pop_back(); }
  reverse(all(q)); return {q,r}; }
pair<poly,poly> divide(poly &a, poly &b){  //returns {quotient,remainder}
  int m=sz(a),n=sz(b),MAGIC=750; if(m<n) return {{0},a};
  if(min(m-n,n)<MAGIC)return divslow(a,b);
  poly ap=a; reverse(all(ap));
  poly bp=b; reverse(all(bp)); bp=invert(bp,m-n);
  poly q=multiply(ap,bp); q.resize(sz(q)+m-n-sz(q)+1,0);
  reverse(all(q)); poly bq=multiply(b,q);
  fore(i,0,sz(bq)) bq[i]=submod(0,bq[i]); poly r=add(a,bq);
  return {q,r}; } vector<poly> tree;
void filltree(vector<tf> &x){ int k=sz(x); tree.resize(2*k);
  fore(i,k,2*k) tree[i]={submod(0,x[i-k]),1};
  for(int i=k-1;i;i--) tree[i]=multiply(tree[2*i],tree[2*i+1]); }
vector<tf> evaluate(poly &a, vector<tf> &x){
  filltree(x); int k=sz(x); vector<poly> ans(2*k);
  ans[1]=divide(a,tree[1]).snd;
  fore(i,2,2*k) ans[i]=divide(ans[i>>1],tree[i]).snd;
  vector<tf> r; fore(i,0,k) r.pb(ans[i+k][0]); return r; }
poly derivate(poly &p){poly ans(sz(p)-1); 
  fore(i,1,sz(p)) ans[i-1]=mulmod(p[i],i); return ans; }
poly interpolate(vector<tf> &x, vector<tf> &y){
  filltree(x); poly p=derivate(tree[1]); int k=sz(y);
  vector<tf> d=evaluate(p,x); vector<poly> intree(2*k);
  fore(i,k,2*k) intree[i]={mulmod(y[i-k],inv(d[i-k]))};
  for(int i=k-1;i;i--){
    poly p1=multiply(tree[2*i],intree[2*i+1]);
    poly p2=multiply(tree[2*i+1],intree[2*i]);
    intree[i]=add(p1,p2); } return intree[1]; }
const int maxn=200005; struct kdtree {
  int xl,xr,yl,yr,zl,zr,max,flag; //flag=0:x axis 1:y 2:z
} tr[5000005];
int N,M,lastans,xq,yq,a[maxn],pre[maxn],nxt[maxn];
int x[maxn],y[maxn],z[maxn],wei[maxn];
int xc[maxn],yc[maxn],zc[maxn],wc[maxn],hash[maxn],biao[maxn];
bool cmp1(int a,int b) { return x[a]<x[b]; }
bool cmp2(int a,int b) { return y[a]<y[b]; }
bool cmp3(int a,int b) { return z[a]<z[b]; }
void makekdtr(int node,int l,int r,int flag) {
  if (l>r) { tr[node].max=-INFL; return; }
  int xl=INFL,xr=-INFL,yl=INFL,yr=-INFL,zl=INFL,zr=-INFL,maxc=-INFL;
  for (int i=l;i<=r;i++)
    xl=min(xl,x[i]),xr=max(xr,x[i]),yl=min(yl,y[i]),yr=max(yr,y[i]),
    zl=min(zl,z[i]),zr=max(zr,z[i]),maxc=max(maxc,wei[i]),
    xc[i]=x[i],yc[i]=y[i],zc[i]=z[i],wc[i]=wei[i],biao[i]=i;
  tr[node].flag=flag; tr[node].xl=xl,tr[node].xr=xr,tr[node].yl=yl;
  tr[node].yr=yr,tr[node].zl=zl,tr[node].zr=zr; tr[node].max=maxc;
  if (l==r) return; if (flag==0) sort(biao+l,biao+r+1,cmp1);
  if (flag==1) sort(biao+l,biao+r+1,cmp2);
  if (flag==2) sort(biao+l,biao+r+1,cmp3);for (int i=l;i<=r;i++)
x[i]=xc[biao[i]],y[i]=yc[biao[i]],z[i]=zc[biao[i]],wei[i]=wc[biao[i]];
  makekdtr(node*2,l,(l+r)/2,(flag+1)%3);
  makekdtr(node*2+1,(l+r)/2+1,r,(flag+1)%3);}
int getmax(int node,int xl,int xr,int yl,int yr,int zl,int zr) {  
  xl=max(xl,tr[node].xl);xr=min(xr,tr[node].xr);
  yl=max(yl,tr[node].yl);yr=min(yr,tr[node].yr);
  zl=max(zl,tr[node].zl);zr=min(zr,tr[node].zr);
  if (tr[node].max==-INFL) return 0;
  if ((xr<tr[node].xl)||(xl>tr[node].xr)) return 0;
  if ((yr<tr[node].yl)||(yl>tr[node].yr)) return 0;
  if ((zr<tr[node].zl)||(zl>tr[node].zr)) return 0;
  if ((tr[node].xl==xl)&&(tr[node].xr==xr)&&
    (tr[node].yl==yl)&&(tr[node].yr==yr)&&
    (tr[node].zl==zl)&&(tr[node].zr==zr)) return tr[node].max; 
  else return max(getmax(node*2,xl,xr,yl,yr,zl,zr),
        getmax(node*2+1,xl,xr,yl,yr,zl,zr)); }//N 3Drect with weights
// find the maximum weight containing the given 3D-point
struct mylazy { ll lazy1 = 0,lazy2 = INF;
    bool operator==(const mylazy& otr) {
        return lazy1 == otr.lazy1 && lazy2 == otr.lazy2; }
    mylazy& operator=(const mylazy& otr) { lazy1 = otr.lazy1;   lazy2 = otr.lazy2;
        return *this;}
};
struct node{
    ll sumpw2, sum;
    size_t csz = 0;
    mylazy lazy;
    using value = ll;
    using lzy = mylazy;
    void upd(value val0) { //only if node is leaf
        sum = val0;
        sumpw2 = val0 * val0;
        csz = 1;
    }
};
void calclazy(node& act) { //take care
    if (act.lazy.lazy2 != INF) {
        act.sumpw2 = (act.lazy.lazy2 * act.lazy.lazy2) * act.csz;
        act.sum = act.lazy.lazy2 * act.csz;
    }
    if (act.lazy.lazy1 != 0) {
        act.sumpw2 += (act.lazy.lazy1* act.lazy.lazy1) * act.csz + 2 * act.sum * act.lazy.lazy1;
        act.sum += act.lazy.lazy1 *act.csz; 
    }
} //lazy still exist

node join(const node izq,const node der) {
    static node dum1; dum1 = izq; calclazy(dum1);
    static node dum2; dum2 = der; calclazy(dum2);
    node res;
    res.sumpw2 = dum1.sumpw2 + dum2.sumpw2;
    res.sum = dum1.sum + dum2.sum;
    res.csz = dum1.csz + dum2.csz;
    return res;
}
void pushlazy(node &act,const int& l,const int& r, node* t) { 
    if (act.lazy == mylazy{0,INF})  return;
    calclazy(act);
    if (l == r) { act.lazy.lazy1 = 0; act.lazy.lazy2 = INF; return; }
    if (act.lazy.lazy2 != INF) { t[l].lazy = t[r].lazy = {0,act.lazy.lazy2}; }
    t[l].lazy.lazy1  += act.lazy.lazy1, t[r].lazy.lazy1 += act.lazy.lazy1;
    act.lazy = {0, INF};
}
template <typename nodo> // sgtree is index 1
class Segtree{   //nodo needs val
#define idxtree  int mid = (b + e) / 2, l = node * 2 + 1, r = l + 1;
using T = typename  nodo::value;
using L = typename  nodo::lzy; // lazy
public:
T ar[tam];
void init(int b, int e, int node) {
	if(b == e) {
		t[node].upd(ar[b]);
		return; }
	int mid = (b + e) / 2, l = node * 2 + 1, r = l + 1;
	init(b, mid, l);    init(mid + 1, e, r);
	t[node] = join(t[l], t[r]);
}
nodo qry(int b, int e, int node, int i, int j) { //check if b>e & i>j
    idxtree;
    pushlazy(t[node], l, r,t);
	if(b >= i && e <= j)
		return t[node];
	if(mid < i)
		return qry(mid + 1, e, r, i, j);
	if(mid >= j)
		return qry(b, mid, l, i, j);
	return join(qry(b, mid, l, i, j), qry(mid + 1, e, r, i, j));
}
void upd0(int b, int e, int node, int pos, const T val) {
    idxtree;
    pushlazy(t[node], l, r,t);
	if(b == e) {t[node].upd(val);return;}
	if(mid < pos)
		upd(mid + 1, e, r, pos, val);
	else
		upd(b, mid, l, pos, val);
	t[node] = join(t[l], t[r]);
}
void upd1(int b, int e, int node, int i, int j, const L& val)  {
    if (b > e ||  b > j  || e < i) return;
    idxtree;
    pushlazy(t[node], l, r, t);
	if(b >= i && e <= j) {
        t[node].lazy = val;
        pushlazy(t[node], l, r, t);
        return;
    }
    upd1(b, mid, l, i, j, val);
    upd1(mid + 1, e, r, i, j, val);
	t[node] = join(t[l], t[r]);
}
nodo t[4 * tam];
};


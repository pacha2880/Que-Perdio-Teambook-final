// https://www.spoj.com/problems/ADAJOBS/ AC
#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// #include <ext/rope>
// #define int ll
#define mp				make_pair
#define pb				push_back
#define all(a)			(a).begin(), (a).end()
#define sz(a)			(int)a.size()
#define eq(a, b)     	(fabs(a - b) < EPS)
#define md(a, b)		((a) % b + b) % b
#define mod(a)			md(a, MOD)
#define _max(a, b) ((a) > (b) ? (a) : (b))
#define srt(a)			sort(all(a))
#define mem(a, h)		memset(a, (h), sizeof(a))
#define f 				first
#define s 				second
#define forn(i, n)			for(int i = 0; i < n; i++)
#define fore(i, b, e)	for(int i = b; i < e; i++)
#define forg(i, b, e, m)	for(int i = b; i < e; i+=m)
#define index	int mid = (b + e) / 2, l = node * 2 + 1, r = l + 1;
#define DBG(x) cerr<<#x<<" = "<<(x)<<endl
#define RAYA cerr<<"=============================="<<endl
// int in(){int r=0,c;for(c=getchar();c<=32;c=getchar());if(c=='-') return -in();for(;c>32;r=(r<<1)+(r<<3)+c-'0',c=getchar());return r;}


using namespace std;
// using namespace __gnu_pbds;
// using namespace __gnu_cxx;

// #pragma GCC target ("avx2")
// #pragma GCC optimization ("O3")
// #pragma GCC optimization ("unroll-loops")

typedef long long 		ll;
typedef long double ld;	
typedef unsigned long long 		ull;
typedef pair<int, int>  ii;
typedef pair<pair<int, int>, int> iii;
typedef vector<int>     vi;
typedef vector<ii>      vii;
typedef vector<ll>      vll;
// typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
// find_by_order kth largest  order_of_key <
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// rng
const int tam = 100010;
const int MOD = 1000000007;
const int MOD1 = 998244353;
const double DINF=1e100;
const double EPS = 1e-9;
const double PI = acos(-1); 
struct vertex {
    int go[26], pch, par, link = -1, super = -1, leaf = MOD;
    vertex(): link(0), super(MOD) { mem(go, -1); }
    vertex(int ch, int from): pch(ch), par(from) { mem(go, -1); }
};
vector<vertex> t(1);
void add(string &s, int pos) {
    int node = 0;
    for(char ch : s)
    {
        ch -= 'a';
        if(t[node].go[ch] == -1)
            t[node].go[ch] = t.size(); t.emplace_back(ch, node);
        node = t[node].go[ch];
    }
    t[node].leaf = min(t[node].leaf, pos);
}
int go(int node, char c);
int suff(int node) {
    if(t[node].link == -1)
        t[node].link = t[node].par == 0 ? 0 : go(suff(t[node].par), t[node].pch);
    return t[node].link;
}
int go(int node, char ch) {
    if(t[node].go[ch] == -1)
        t[node].go[ch] = node == 0 ? 0 : go(suff(node), ch);
    return t[node].go[ch];
}
int super(int v) {
	if(t[v].super == -1)
        t[v].super = min(t[v].leaf, super(suff(v)));
	return t[v].super;
}
string matching(int pos, string s)
{
    int node = 0;
    for(char ch : s)
    {
        ch -= 'a';
        node = go(node, ch);
        if(super(node) < pos)
            return "YES";
    }
    return "NO";
}
signed main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// freopen("asd.txt", "r", stdin);
	// freopen("qwe.txt", "w", stdout);
	int n;
    cin>>n;
    vector<pair<int, string>> ar;
    fore(i, 0, n)
    {
        int a;
        string s;
        cin>>a>>s;
        if(a)
            ar.pb({i, s});
        else
            add(s, i);
    }
    for(auto cat : ar)
        cout<<matching(cat.f, cat.s)<<'\n';
	return 0;
}

// Se vuelve más fácil,
// cada día es un poco más fácil, pero tienes que hacerlo cada día,
// es la parte difícil, pero se vuelve más fácil.
// Crecer duele.

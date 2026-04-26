void euclid(ll a, ll b, ll &x, ll &y) {
  if (b) euclid(b, a%b, y, x), y -= x*(a/b);
  else x = 1, y = 0; }
//find (x,y) t.q. a*x+b*y=c or return false if it's not possible
//[x + k*b/gcd(a, b), y - k*a/gcd(a, b)] are also solutions
bool diof(ll a, ll b, ll c, ll &x, ll &y){
  euclid(abs(a), abs(b), x, y); ll g = abs(__gcd(a, b));
  if(c % g) return false; x *= c / g; y *= c / g;
  if(a < 0) x = -x; if(b < 0) y = -y; return true; }
const double DINF=1e100;
struct pt {
  double x,y;
  pt(double x, double y):x(x),y(y){} pt(){}
  double norm2(){return *this**this;}
  double norm(){return sqrt(norm2());}
  bool operator==(pt p){return abs(x-p.x)<=EPS&&abs(y-p.y)<=EPS;}
  pt operator+(pt p){return pt(x+p.x,y+p.y);}
  pt operator-(pt p){return pt(x-p.x,y-p.y);}
  pt operator*(double t){return pt(x*t,y*t);}
  pt operator/(double t){return pt(x/t,y/t);}
  double operator*(pt p){return x*p.x+y*p.y;}
  double angle(pt p){ // redefine acos for values out of range
  return acos(*this*p/(norm()*p.norm()));}
  pt unit(){return *this/norm();}
  double operator%(pt p){return x*p.y-y*p.x;}
  bool operator<(pt p)const{ // for convex hull
  return x<p.x-EPS||(abs(x-p.x)<=EPS&&y<p.y-EPS);}
  bool left(pt p, pt q){ // is it to the left of directed line pq?
  return (q-p)%(*this-p)>EPS;}
  pt rot(pt r){return pt(*this%r,*this*r);}
  pt rot(double a){return rot(pt(sin(a),cos(a)));} };
pt ccw90(1,0); pt cw90(-1,0); int sgn2(double x){return x<0?-1:1;}
struct ln {
  pt p,pq; ln(pt p, pt q):p(p),pq(q-p){} ln(){}
  bool has(pt r){return dist(r)<=EPS;}
  bool seghas(pt r){return has(r)&&(r-p)*(r-(p+pq))<=EPS;}
  bool operator/(ln l){return abs(pq.unit()%l.pq.unit())<=EPS;}
  bool operator==(ln l){return *this/l&&has(l.p);}
  pt operator^(ln l){ // intersection
  if(*this/l)return pt(DINF,DINF); pt r=l.p+l.pq*((p-l.p)%pq/(l.pq%pq));
  return r; }
  double angle(ln l){return pq.angle(l.pq);}
  int side(pt r){return has(r)?0:sgn2(pq%(r-p));}
  pt proj(pt r){return p+pq*((r-p)*pq/pq.norm2());}
  pt ref(pt r){return proj(r)*2-r;}
  double dist(pt r){return (r-proj(r)).norm();}
  ln rot(auto a){return ln(p,p+pq.rot(a));} };
ln bisector(ln l, ln m){ // angle bisector
  pt p=l^m; return ln(p,p+l.pq.unit()+m.pq.unit()); }
ln bisector(pt p, pt q){ return ln((p+q)*.5,p).rot(ccw90); }
// polygon intersecting left side of halfplanes
struct halfplane:public ln{
  double angle; halfplane(){}
  halfplane(pt a,pt b){p=a; pq=b-a; angle=atan2(pq.y,pq.x);}
  bool operator<(halfplane b)const{return angle<b.angle;}
  bool out(pt q){return pq%(q-p)<-EPS;} };
vector<pt> intersect(vector<halfplane> b){
  vector<pt>bx={{DINF,DINF},{-DINF,DINF},{-DINF,-DINF},{DINF,-DINF}};
  fore(i,0,4) b.pb(halfplane(bx[i],bx[(i+1)%4]));
  sort(all(b)); int n=sz(b),q=1,h=0;
  vector<halfplane> c(sz(b)+10);
  fore(i,0,n){
  while(q<h&&b[i].out(c[h]^c[h-1])) h--;
  while(q<h&&b[i].out(c[q]^c[q+1])) q++; c[++h]=b[i];
  if(q<h&&abs(c[h].pq%c[h-1].pq)<EPS){
    if(c[h].pq*c[h-1].pq<=0) return {}; h--;
    if(b[i].out(c[h].p)) c[h]=b[i]; } }
  while(q<h-1&&c[q].out(c[h]^c[h-1]))h--;
  while(q<h-1&&c[h].out(c[q]^c[q+1]))q++;
  if(h-q<=1)return {}; c[h+1]=c[q]; vector<pt> s;
  fore(i,q,h+1) s.pb(c[i]^c[i+1]); return s; }
struct pol {
  int n;vector<pt> p; pol(){}
  pol(vector<pt> _p){p=_p;n=p.size();}
  double area(){
    double r=0.; fore(i,0,n)r+=p[i]%p[(i+1)%n];
    return abs(r)/2; // negative if CW, positive if CCW
  } };
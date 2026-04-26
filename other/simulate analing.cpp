
  vi pref; for(int i=1;i<=n;i++)pref.pb(i);
  shuffle(pref.begin(),pref.end(),rng);
  int res=costo(pref);vi respuesta=resi;double tempereatura=1e6;
  while(clock() / (double) CLOCKS_PER_SEC <= 0.975749){
    int a=uniform_int_distribution<int>(0,n-1)(rng);
    int b=uniform_int_distribution<int>(0,n-2)(rng);
    if(a==b){ b++; if(b==n)b=0;}vi next=pref;
    swap(next[a],next[b]);/*funcion vecino*/int nextCosto=costo(next);
    if(nextCosto<res){ res=nextCosto;respuesta=resi;pref=next;}
    else{double proba=exp((res-nextCosto)/tempereatura);
      double r=uniform_real_distribution<double>(0,1)(rng);
      if(r<proba){res=nextCosto;respuesta=resi;pref=next;}}
    tempereatura*=0.9999;}
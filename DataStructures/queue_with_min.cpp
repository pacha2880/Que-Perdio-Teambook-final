struct quemin
{
	pair<int,int> bo[100010], to[100010];
	int boto = -1, toto = -1, ax;
	void push(int n)
	{
		ax = boto + 1;
		if(boto == -1)
			bo[ax] = mp(n, n);	
		else
			bo[ax] = mp(n, min(bo[boto].s, n));
		boto++;
	}
	void pop()
	{
		if(toto == -1)
		{
			while(boto > -1)
			{
				ax = toto + 1;
				if(toto == -1)
					to[ax] = mp(bo[boto].f, bo[boto].f);
				else
					to[ax] = mp(bo[boto].f, min(bo[boto].f, to[toto].s));
				toto++;
				boto--;
			}
		}
		if(toto > -1)
			toto--;
	}
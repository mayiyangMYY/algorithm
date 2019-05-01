void dfs(int u,int f,int depth)
{
	father[0][u]=f;
	dep[u]=depth;
	for (int i=0;i<G[u].size();++i)
	{
		int to=G[u][i];
		if (to==f) continue;
		dfs(to,u,depth+1);
	}
}

void init()
{
	dfs(1,-1,0);
	for (int i=1;i<=17;++i)
	{
		for (int j=1;j<=n;++j)
		{
			father[i][j]=father[i-1][father[i-1][j]];
		}
	}
}

int lca(int u,int v)
{
	if (dep[u]<dep[v]) swap(u,v);
	for (int i=17;i>=0;--i)
	{
		if (dep[u]-(1<<i)>=dep[v])
		{
			u=father[i][u];
		}
	}
	if (u==v) return u;
	for (int i=17;i>=0;--i)
	{
		if (father[i][u]!=father[i][v])
		{
			u=father[i][u],v=father[i][v];
		}
	}
	return father[0][u];
}

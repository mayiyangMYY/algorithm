void dfs(int u,int f)
{
	++dfs_clock;
	dfn[u]=low[u]=dfs_clock;
	int child=0;
	for (int i=0;i<G[u].size();++i)
	{
		int to=G[u][i];
		if (!dfn[to])
		{
			++child;
			dfs(to,u);
			low[u]=min(low[u],low[to]);
			if (low[to]>=dfn[u])
			{
				iscut[u]=1;
			} 
		}
		else if (to!=f)
		{
			low[u]=min(low[u],dfn[to]);//!!!
		}
	}
	if (f<0&&child==1) iscut[u]=0;
}

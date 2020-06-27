void dfs(int x)
{
	++dfs_clock;
	dfn[x]=low[x]=dfs_clock;
	S[++top]=x;
	for (int i=first[x];i!=-1;i=nxt[i])
	{
		int to=point[i];
		if (!dfn[to])
		{
			dfs(to);
			checkmin(low[x],low[to]);
		}
		else if (!sccno[to])
		{
			checkmin(low[x],dfn[to]);
		}
	}
	if (low[x]==dfn[x])
	{
		int tmp;
		++scc_cnt;
		for (;;)
		{
			tmp=S[top]; --top;
			sccno[tmp]=scc_cnt;
			if (tmp==x) break;
		}
	}
}//scc

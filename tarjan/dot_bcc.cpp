void dfs(int x,int f)
{
	++dfs_clock;
	dfn[x]=low[x]=dfs_clock;
	int child=0;
	for (int i=first[x];i!=-1;i=nxt[i])
	{
		int to=point[i];
		Edge e(x,to);
		if (!dfn[to])
		{
			++child;
			S[++top]=e;
			dfs(to,x);
			checkmin(low[x],low[to]);
			if (low[to]>=dfn[x])
			{
				is_cut[x]=1;
				++bcc_cnt;
				bcc[bcc_cnt].clear();
				for (;;)
				{
					Edge e=S[top]; --top;
					if (bccno[e.u]!=bcc_cnt)
					{
						bcc[bcc_cnt].push_back(e.u);
						bccno[e.u]=bcc_cnt;
					}
					if (bccno[e.v]!=bcc_cnt)
					{
						bcc[bcc_cnt].push_back(e.v);
						bccno[e.v]=bcc_cnt;
					}
					if (e.u==x&&e.v==to) break;
				}
			}
		}
		else if (dfn[to]<dfn[x]&&to!=f) //important
		{
			S[++top]=e;
			checkmin(low[x],dfn[to]);
		}
	}
	if (f<=0&&child==1) is_cut[x]=0;
}

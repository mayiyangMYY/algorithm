void dfs2(int x,int pre_edge)
{
	bccno[x]=bcc_cnt;
	for (int i=first[x];i!=-1;i=nxt[i])
	{
		int to=point[i];
		if (i==(pre_edge^1)||bridge[i]||bccno[to]) continue;
		dfs2(to,i);
	}
}//edge_bcc

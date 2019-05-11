void dfs(int u,int f)
{
    dfn[u]=low[u]=++dfs_clock;
    for (int i=first[u];i!=-1;i=nxt[i])
    {
    	if ((i^1)==f) continue; //要存上一条边，不要存点
        int to=point[i];
        if (!dfn[to])
        {
            dfs(to,i);
            low[u]=min(low[u],low[to]);
            if (low[to]>dfn[u])
            {
                bridge[i]=bridge[i^1]=1;
            }
        }
        else
        {
            low[u]=min(low[u],dfn[to]);//!!!
        }
    }
}

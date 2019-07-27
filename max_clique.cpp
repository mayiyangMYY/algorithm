const int N=55;
int n,G[N][N],dp[N],ans=0,S[N];
//dp[i] represents the maximum number of point from i to n that makes up a clique 
void init()
{
    for (int i=1;i<=n;++i)
    {
        for (int j=1;j<=n;++j)
        {
            read(G[i][j]);
        }
    }
}

bool check(int depth,int x)
{
    for (int i=1;i<=depth;++i)
    {
        if (!G[S[i]][x]) return 0;
    }
    return 1;
}

//S works as a stack
void dfs(int x,int depth)
{
    if (depth+n-x+1<=ans||depth+dp[x]<=ans) return;
    //cut branches
    if (depth>ans) ans=depth;
    for (int i=x;i<=n;++i)
    {
        if (check(depth,i))
        {
            S[depth+1]=i;
            dfs(i,depth+1);
            S[depth+1]=0;
        }
    }
}

int max_clique()
{
    memset(dp,0,sizeof dp);
    memset(S,0,sizeof S);
    ans=0;
    for (int i=n;i>=1;--i)
    {
        S[1]=i;
        dfs(i+1,1);
        dp[i]=ans;
    }
    return ans;
}

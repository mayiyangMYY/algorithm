char s[N];
int n,Rnk[N<<1],cnt[N],P[N],Q[N],sa[N],height[N];
void get_sa()
{
    for (int i=0;i<=200;++i) cnt[i]=0;
    for (int i=1;i<=n;++i) cnt[s[i]]=1;
    for (int i=1;i<=200;++i) cnt[i]+=cnt[i-1];
    for (int i=1;i<=n;++i) Rnk[i]=cnt[s[i]];
    for (int now=1;now<n;now<<=1)
    {
        for (int i=0;i<=n;++i) cnt[i]=0;
        cnt[0]=now;
        for (int i=now+1;i<=n;++i) ++cnt[Rnk[i]];
        for (int i=1;i<=n;++i) cnt[i]+=cnt[i-1];
        for (int i=n;i>=1;--i)
        {
            int tmp=Rnk[i+now];
            P[cnt[tmp]]=i; --cnt[tmp];
        } 
        for (int i=0;i<=n;++i) cnt[i]=0;
        for (int i=1;i<=n;++i) ++cnt[Rnk[P[i]]];
        for (int i=1;i<=n;++i) cnt[i]+=cnt[i-1];
        for (int i=n;i>=1;--i)
        {
            Q[cnt[Rnk[P[i]]]]=P[i];
            --cnt[Rnk[P[i]]];
        }
        int tmp=0;
        for (int i=1;i<=n;++i)
        {
            if (Rnk[Q[i]]!=Rnk[Q[i-1]]||Rnk[Q[i]+now]!=Rnk[Q[i-1]+now]) ++tmp;
            P[i]=tmp;
        }
        for (int i=1;i<=n;++i) Rnk[Q[i]]=P[i];
        if (tmp==n) break;
    }
    for (int i=1;i<=n;++i) sa[Rnk[i]]=i;
    for (int i=1;i<=n;++i) printf("%d%c",sa[i]," \n"[i==n]);
}

//height[i] -> the length of LCP of SA[i-1] and SA[i]
//h[i]=height[Rnk[i]]   h[i]>=h[i-1]-1
//LCP(suffix i,suffix j)=RMQ(height,rnk[i]+1,rnk[j]);
void get_height()
{
    int tmp=0;
    for (int i=1;i<=n;++i)
    {
        if (tmp) --tmp;
        int j=sa[Rnk[i]-1];
        while (s[j+tmp]==s[i+tmp]) ++tmp;
        height[Rnk[i]]=tmp;
    }
}

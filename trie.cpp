struct Trie
{
	int a[maxn][2],sz,cnt[maxn];
    inline void init() {
        a[1][0]=a[1][1]=0;
        cnt[1]=0,sz=1;
    }
    inline void insert(int x)
    {
        int now=1;
        for (int i=31;i>=0;--i)
        {
            int k=(x>>i&1);
            if (!a[now][k])
            {
                ++sz;
                a[now][k]=sz;
                a[sz][0]=a[sz][1]=0;
                cnt[sz]=0;
            }
            ++cnt[now];
            now=a[now][k];
        }
        ++cnt[now];
    }
    
    inline void modify(int x,int delta)
    {
        int now=1;
        for (int i=31;i>=0;--i)
        {
            int k=(x>>i&1);
            cnt[now]+=delta;
            now=a[now][k];
        }
        cnt[now]+=delta;
    }

    inline int query(int x)
    {
        int now=1,ans=0;
        for (int i=31;i>=0;--i)
        {
            int k=(x>>i&1);
            if (a[now][k^1] && cnt[a[now][k^1]])
            {
                now=a[now][k^1];
                ans|=(1<<i);
            }
            else now=a[now][k];
        }
        return ans;
    }
};

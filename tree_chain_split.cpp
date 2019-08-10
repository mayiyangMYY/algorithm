#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <ctime>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <queue>
using namespace std;
#ifdef enable_ll
    #define int long long
#endif
#ifdef DEBUG
    #define out(u) cout<<u<<" "
    #define outln(u) cout<<u<<endl
    #define see(u) cout<<#u<<"="<<u<<" "
    #define seeln(u) cout<<#u<<"="<<u<<endl
    #define line cout<<"---------------------\n"
#else
    #define out(u)
    #define outln(u)
    #define see(u)
    #define seeln(u)
    #define line
#endif
#define m_p make_pair
#define pii pair<int,int>
#define piii pair<int,pii>
template <class T> void read(T &u)
{
    u=0; char c=getchar(); int flag=0;
    while (c<'0'||c>'9') flag|=(c=='-'),c=getchar();
    while (c>='0'&&c<='9') u=(u<<3)+(u<<1)+(c^48),c=getchar();
    if (flag) u=-u;
}
bool checkmin(int &a,int b){return (b<a ? a=b,1 : 0);}
bool checkmax(int &a,int b){return (b>a ? a=b,1 : 0);}
const int N=100005;
const int M=100005;
const int inf=1000000000;
int n,m,r,P,a[N];
int e=1,nxt[M<<1],point[M<<1],first[N];
int fa[N],dep[N];
int son[N],sz[N];
int top[N],dfs_clock=0,id[N],rnk[N];
void add_edge(int x,int y)
{
    ++e;
    point[e]=y;
    nxt[e]=first[x];
    first[x]=e;
}

void dfs1(int x,int f,int depth)
{
    fa[x]=f; sz[x]=1; dep[x]=depth;
    int mx=-1;
    for (int i=first[x];i!=-1;i=nxt[i])
    {   
        int to=point[i];
        if (to==f) continue;
        dfs1(to,x,depth+1);
        sz[x]+=sz[to];
        if (checkmax(mx,sz[to]))
        {
            son[x]=to;
        }
    }
}

void dfs2(int x,int ancestor)
{
    top[x]=ancestor;
    ++dfs_clock; id[x]=dfs_clock;
    rnk[dfs_clock]=x;
    if (!son[x]) return;
    dfs2(son[x],ancestor);
    for (int i=first[x];i!=-1;i=nxt[i])
    {
        int to=point[i];
        if (to==fa[x]||to==son[x]) continue;
        dfs2(to,to);
    }
} 

namespace seg
{
    int sum[N<<2],tag[N<<2];
    void push_up(int x)
    {
        sum[x]=sum[x+x]+sum[x+x+1];
    }
    
    void push_down(int x,int l,int mid,int r)
    {
        if (tag[x])
        {
            tag[x+x]+=tag[x];
            tag[x+x+1]+=tag[x];
            sum[x+x]+=tag[x]*(mid-l+1);
            sum[x+x+1]+=tag[x]*(r-mid);
            tag[x]=0;
        }
    }
    
    void build(int x,int l,int r)
    {
        if (l==r)
        {
            sum[x]=a[rnk[l]];
            tag[x]=0;
            return;
        }
        int mid=(l+r)>>1;
        build(x+x,l,mid);
        build(x+x+1,mid+1,r);
        push_up(x);
    }
    
    void update(int x,int l,int r,int L,int R,int val)
    {
        if (L<=l&&r<=R)
        {
            sum[x]+=val*(r-l+1);
            tag[x]+=val;
            return;
        }
        int mid=(l+r)>>1;
        push_down(x,l,mid,r);
        if (L<=mid) update(x+x,l,mid,L,R,val);
        if (R>mid) update(x+x+1,mid+1,r,L,R,val);
        push_up(x);
    }
    
    int query(int x,int l,int r,int L,int R)
    {
        if (L<=l&&r<=R)
        {
            return sum[x];
        }
        int mid=(l+r)>>1,ans=0;
        push_down(x,l,mid,r);
        if (L<=mid) ans+=query(x+x,l,mid,L,R);
        if (R>mid) ans+=query(x+x+1,mid+1,r,L,R);
        return ans;
    }
}

namespace TCS //tree_chain_split
{
    void upd_chain(int x,int y,int z)
    {
        while (top[x]!=top[y])
        {
            if (dep[top[x]]<dep[top[y]]) swap(x,y);
            seg::update(1,1,n,id[top[x]],id[x],z);
            x=fa[top[x]];
        }
        seg::update(1,1,n,min(id[x],id[y]),max(id[x],id[y]),z);
    }

    int query_chain(int x,int y)
    {
        int ans=0;
        while (top[x]!=top[y])
        {
            if (dep[top[x]]<dep[top[y]]) swap(x,y);
            ans+=seg::query(1,1,n,id[top[x]],id[x]);
            x=fa[top[x]];
        }
        ans+=seg::query(1,1,n,min(id[x],id[y]),max(id[x],id[y]));
        return ans;
    }

    void upd_subtree(int x,int y)
    {
        seg::update(1,1,n,id[x],id[x]+sz[x]-1,y);
    }

    int query_subtree(int x)
    {
        return seg::query(1,1,n,id[x],id[x]+sz[x]-1);
    }
}

void init()
{
    read(n); read(m); read(r); read(P);
    for (int i=1;i<=n;++i)
    {
        read(a[i]);
    }
    int x,y;
    memset(first,-1,sizeof first);
    for (int i=1;i<n;++i)
    {
        read(x); read(y);
        add_edge(x,y);
        add_edge(y,x);
    }
    dfs1(r,0,0);
    dfs2(r,r);
    seg::build(1,1,n);
}

void solve()
{
    int opt,x,y,z;
    while (m--)
    {
        read(opt);
        if (opt==1)
        {
            read(x); read(y); read(z);
            TCS::upd_chain(x,y,z);
        }
        if (opt==2)
        {
            read(x); read(y);
            printf("%d\n",TCS::query_chain(x,y)%P);
        }   
        if (opt==3)
        {
            read(x); read(y);
            TCS::upd_subtree(x,y);
        }
        if (opt==4)
        {
            read(x);
            printf("%d\n",TCS::query_subtree(x)%P);
        }   
    }
}
        
#undef int
int main()
{
    init();
    solve();
    return 0;
}

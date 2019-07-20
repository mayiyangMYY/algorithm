#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#ifdef enable_ll
    #define int long long
#endif
#ifdef DEBUG
    #define out(x) cout<<x<<" "
    #define outln(x) cout<<x<<endl
    #define see(x) cout<<#x<<"="<<x<<" "
    #define seeln(x) cout<<#x<<"="<<x<<endl
#else
    #define out(x)
    #define outln(x)
    #define see(x)
    #define seeln(x)
#endif
#define m_p make_pair
#define pii pair<int,int>
#define piii pair<int,pii>
template <class T> void read(T &x)
{
    x=0; char c=getchar(); int flag=0;
    while (c<'0'||c>'9') flag|=(c=='-'),c=getchar();
    while (c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    if (flag) x=-x;
}
template <class T> void write(T x)
{
    if (x<0) x=-x,putchar('-');
    if (x>9) write(x/10);
    putchar(x%10+48);
}
template <class T> void write_blank(T x)
{
    write(x);
    putchar(' ');
}
template <class T> void writeln(T x)
{
    write(x);
    putchar('\n');
}

template <class T> bool checkmin(T &a,T b){return b<a ? a=b,1 : 0;}
template <class T> bool checkmax(T &a,T b){return b<a ? a=b,1 : 0;}
template <class T> T min(T &a,T &b){return a<b ? a : b;}
template <class T> T max(T &a,T &b){return a>b ? a : b;}
const int N=100005;
int ch[N][2],root=0,tot_sz=0;
int sz[N],cnt[N],val[N],pri[N];
//big root heap
void print(int now)
{
    if (!now) return;
    printf("%d %d %d %d %d %d %d\n",now,val[now],ch[now][0],ch[now][1],pri[now],sz[now],cnt[now]);
    print(ch[now][0]);
    print(ch[now][1]);
}
void debug()
{
    see(root);
    seeln(tot_sz);
    print(root);
}

int ran()
{
    static long long seed=19260817;
    static long long mod=1000000007;
    seed|=(seed<<6);
    seed^=(seed>>7);
    seed|=(seed<<3);
    seed%=mod;
    return (int)seed;
}

void push_up(int x)
{
    sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+cnt[x];
}

void rotate(int &x,int d)
{
    int y=ch[x][d];
    ch[x][d]=ch[y][d^1];
    ch[y][d^1]=x;
    push_up(x),push_up(y);
    x=y;
}//d=0 ->right rotate     d=1 ->left rotate

void insert(int &now,int x)
{
    if (!now)
    {
        now=++tot_sz;
        ch[tot_sz][0]=ch[tot_sz][1]=0;
        sz[tot_sz]=cnt[tot_sz]=1;
        val[tot_sz]=x;
        pri[tot_sz]=ran();
        return;
    }
    ++sz[now];
    if (val[now]==x) ++cnt[now];
    else
    {
        int dir=val[now]<x;
        insert(ch[now][dir],x);
        if (pri[now]<pri[ch[now][dir]]) rotate(now,dir);
    }
}

void remove(int &now,int x)
{
    if (!now) return;
    if (val[now]==x)
    {
        if (cnt[now]>1)
        {
            --cnt[now];
            --sz[now];
        }
        else if (!ch[now][0]||!ch[now][1])
        {
            now=ch[now][0]+ch[now][1];
        }
        else
        {
            int d=pri[ch[now][0]]<pri[ch[now][1]];
            rotate(now,d);
            remove(now,x);
        }
    }
    else
    {
        --sz[now];
        remove(ch[now][x>val[now]],x);
    }
}

int rnk(int x)
{
    int tmp=root,ans=0;
    while (tmp)
    {
        if (val[tmp]>x)
        {
            tmp=ch[tmp][0];
        }
        else if (val[tmp]<x)
        {
            ans+=(sz[ch[tmp][0]]+cnt[tmp]);
            tmp=ch[tmp][1];
        }
        else 
        {
            return ans+sz[ch[tmp][0]]+1;
        }
    }
}

int kth(int x)
{
    int tmp=root;
    while (tmp)
    {
        if (sz[ch[tmp][0]]>=x)
        {
            tmp=ch[tmp][0];
        }
        else if (sz[ch[tmp][0]]+cnt[tmp]<x)
        {
            x-=(sz[ch[tmp][0]]+cnt[tmp]);
            tmp=ch[tmp][1];
        }
        else
        {
            return val[tmp];
        }
    }
}

int pred(int x)
{
    int tmp=root,ans=0;
    while (tmp)
    {
        if (val[tmp]<x)
        {
            ans=val[tmp];
            tmp=ch[tmp][1];
        }
        else
        {
            tmp=ch[tmp][0];
        }
    }
    return ans;
}

int succ(int x)
{
    int tmp=root,ans=0;
    while (tmp)
    {
        if (val[tmp]>x)
        {
            ans=val[tmp];
            tmp=ch[tmp][0];
        }
        else
        {
            tmp=ch[tmp][1];
        }
    }
    return ans;
}

int n,opt,x;
void solve()
{
    read(n);
    while (n--)
    {
        read(opt),read(x);
        if (opt==1) insert(root,x);
        if (opt==2) remove(root,x);
        if (opt==3) writeln(rnk(x));
        if (opt==4) writeln(kth(x));
        if (opt==5) writeln(pred(x));
        if (opt==6) writeln(succ(x));
        #ifdef DEBUG
        debug();
        #endif
    }
}

#undef int
int main()
{
    solve();
    return 0;
}

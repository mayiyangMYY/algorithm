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
int sz[N],val[N],pri[N],fa[N];
void print(int now)
{
    if (!now) return;
    printf("%d %d %d %d %d\n",now,val[now],ch[now][0],ch[now][1],sz[now]);
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
    static long long mod=998244353;
    seed|=(seed<<6);
    seed^=(seed>>7);
    seed|=(seed<<3);
    seed%=mod;
    return (int)seed;
}

void push_up(int x)
{
    sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+1;
}

int NEW(int x)
{
    ++tot_sz;
    ch[tot_sz][0]=ch[tot_sz][1]=0;
    sz[tot_sz]=1;
    val[tot_sz]=x;
    pri[tot_sz]=ran();
    return tot_sz;
}

void split(int now,int num,int &x,int &y)
{
    if (!now)
    {
        x=y=0;
        return;
    }
    if (val[now]<=num)
    {
        x=now;
        split(ch[now][1],num,ch[now][1],y);
    }
    else
    {
        y=now;
        split(ch[now][0],num,x,ch[now][0]);
    }
    push_up(now); //!!!
}

int merge(int x,int y)
{
    if (!x||!y) return x+y;
    if (pri[x]<pri[y])
    {
        ch[x][1]=merge(ch[x][1],y);
        push_up(x); //!!!
        return x;
    }
    else
    {
        ch[y][0]=merge(x,ch[y][0]);
        push_up(y); //!!!
        return y;
    }
}

int kth(int now,int k)
{
    int tmp=now;
    while (tmp)
    {
        if (sz[ch[tmp][0]]>=k)
        {
            tmp=ch[tmp][0];
        }
        else if (sz[ch[tmp][0]]+1==k)
        {
            return tmp;
        }
        else
        {
            k-=(sz[ch[tmp][0]]+1);
            tmp=ch[tmp][1];
        }
    }
}

int n,opt,num,x,y,z;
void solve()
{
    read(n);
    for (int i=1;i<=n;++i)
    {
        read(opt),read(num);
        if (opt==1) 
        {
            split(root,num,x,y);
            root=merge(merge(x,NEW(num)),y);
        }
        else if (opt==2)
        {
            split(root,num,x,y);
            split(x,num-1,x,z);
            z=merge(ch[z][0],ch[z][1]);
            root=merge(merge(x,z),y);
        }
        else if (opt==3)
        {
            split(root,num-1,x,y);
            writeln(sz[x]+1);
            root=merge(x,y);
        }
        else if (opt==4)
        {
            writeln(val[kth(root,num)]);
        }
        else if (opt==5)
        {
            split(root,num-1,x,y);
            writeln(val[kth(x,sz[x])]);
            root=merge(x,y);
        }
        else
        {
            split(root,num,x,y);
            writeln(val[kth(y,1)]);
            root=merge(x,y);
        }
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

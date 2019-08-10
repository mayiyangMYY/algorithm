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
const int N=300005;
const int inf=1000000000;
int n,m;
namespace LCT
{
    int rev[N],fa[N],ch[N][2],v[N],dot[N];
    void init(int n)
    {
        for (int i=0;i<=n;++i)
        {
            rev[i]=fa[i]=ch[i][0]=ch[i][1]=dot[i]=0;
        }
    }

    void push_up(int x)
    {
        dot[x]=dot[ch[x][0]]^dot[ch[x][1]]^v[x];
    }
    
    int get(int x)
    {
        if (!fa[x]) return -1;
        if (ch[fa[x]][0]==x) return 0;
        if (ch[fa[x]][1]==x) return 1;
        return -1;
    }
    
    void push_rev(int x)
    {
        swap(ch[x][0],ch[x][1]);
        rev[x]^=1;
    }

    void push_down(int x)
    {
        if (rev[x])
        {
            if (ch[x][0]) push_rev(ch[x][0]);
            if (ch[x][1]) push_rev(ch[x][1]);
            rev[x]=0;
        }
    }

    void rotate(int x)
    {
        int y=fa[x],z=fa[y],dx=get(x),dy=get(y),w=ch[x][dx^1];
        if (dy!=-1) ch[z][dy]=x; 
        ch[y][dx]=w; ch[x][dx^1]=y;
        if (w) fa[w]=y;
        fa[x]=z; fa[y]=x;
        push_up(y); push_up(x);
    }

    void push_all(int x)
    {
        if (get(x)!=-1) push_all(fa[x]);
        push_down(x);
    }

    void splay(int x)
    {
        push_all(x);   //important!!!!!!
        while (get(x)!=-1)
        {
            int y=fa[x],z=fa[y];
            if (get(y)!=-1)
            {
                if (get(y)==get(x)) rotate(y);
                else rotate(x);
            }
            rotate(x);
        }
        push_up(x);
    }

    void access(int x)
    {
        for (int y=0;x;y=x,x=fa[x])
        {
            splay(x);
            ch[x][1]=y;
            push_up(x);
        }
    }

    void make_root(int x)
    {
        access(x); 
        splay(x);
        push_rev(x);
    }

    int find_root(int x)
    {
        access(x); 
        splay(x);
        while (ch[x][0])
        {
            push_down(x);
            x=ch[x][0];
        }
        splay(x); //ensure the time complexity
        return x;
    }

    void split(int x,int y)
    {
        make_root(x);
        access(y);
        splay(y);
    }
    
    void link(int x,int y)
    {
        make_root(x);
        if (find_root(y)==x) return;
        fa[x]=y;
    }

    void cut(int x,int y)
    {
        make_root(x);
        if (find_root(y)!=x||fa[y]!=x||ch[y][0]) return;
        ch[x][1]=fa[y]=0;
        push_up(x);
    }
}

void init()
{
    read(n); read(m);
    LCT::init(n);
    for (int i=1;i<=n;++i)
    {
        read(LCT::v[i]);
    }
}
 
void solve()
{
    int opt,x,y;
    while (m--)
    {
        read(opt); read(x); read(y);
        if (opt==0) LCT::split(x,y),printf("%d\n",LCT::dot[y]);
        else if (opt==1) LCT::link(x,y);
        else if (opt==2) LCT::cut(x,y);
        else if (opt==3) LCT::splay(x),LCT::v[x]=y;
    }
}
        
#undef int
int main()
{
    init();
    solve();
    return 0;
}

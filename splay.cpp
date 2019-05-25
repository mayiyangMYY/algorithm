#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define see(x) cout<<#x<<" = "<<x<<endl
const int N=200000+29;
int root=0,tot=0,fa[N];
int sz[N],cnt[N],ch[N][2],val[N];
void debug()
{
    cout<<"-----------------------\n";
    see(root);
    for (int i=1;i<=tot;++i)
    {
        see(i);
        see( val[i]);
        see( ch[i][0]);
        see( ch[i][1]);
        see( sz[i]);
    }
}

void push_up(int x)
{
    sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+cnt[x];
}

int get(int x)
{
    return ch[fa[x]][1]==x;
}

void rotate(int x)
{
    int y=fa[x],z=fa[y],dir_x=get(x),dir_y=get(y),w=ch[x][dir_x^1];
    fa[w]=y,ch[y][dir_x]=w;
    fa[x]=z,ch[z][dir_y]=x;
    fa[y]=x,ch[x][dir_x^1]=y;
    push_up(y),push_up(x);
}

void splay(int x,int goal=0)
{
    while (fa[x]!=goal)
    {
        int y=fa[x],z=fa[y];
        if (z==goal) rotate(x);
        else if (get(x)==get(y)) rotate(y),rotate(x);
        else rotate(x),rotate(x);
    }
    if (!goal) root=x;
}

void insert(int x)
{
    int F=root,tmp=root;
    for (;tmp&&val[tmp]!=x;F=tmp,tmp=ch[tmp][x>val[tmp]]) ;
    if (!tmp)
    {
        ++tot,tmp=tot;
        if (F) ch[F][x>val[F]]=tmp;
        sz[tmp]=cnt[tmp]=1,val[tmp]=x;
        fa[tmp]=F,ch[tmp][0]=ch[tmp][1]=0;
    }
    else ++cnt[tmp];
    splay(tmp);
} 

void find(int x)
{
    int tmp=root;
    for (;ch[tmp][x>val[tmp]]&&val[tmp]!=x;tmp=ch[tmp][x>val[tmp]]) ;
    splay(tmp);
}

int Rank(int x)
{
    find(x);
    return sz[ch[root][0]];
}

int kth(int x)
{
    int tmp=root;
    for (;;)
    {
        if (ch[tmp][0]&&sz[ch[tmp][0]]>=x) tmp=ch[tmp][0];
        else if (sz[ch[tmp][0]]+cnt[tmp]<x)
        {
            x-=(sz[ch[tmp][0]]+cnt[tmp]);
            tmp=ch[tmp][1];
        }
        else return tmp;
    }
}

int pre(int x)
{
    find(x);
    int tmp=root;
    if (val[tmp]<x) return tmp;
    else tmp=ch[tmp][0];
    for (;ch[tmp][1];tmp=ch[tmp][1]) ;
    return tmp;
}

int succ(int x)
{
    find(x);
    int tmp=root;
    if (val[tmp]>x) return tmp;
    else tmp=ch[tmp][1];
    for (;ch[tmp][0];tmp=ch[tmp][0]) ;
    return tmp;
}

void remove(int x)
{
    int L=pre(x),R=succ(x);
    splay(L),splay(R,L);
    int now=ch[R][0];
    if (cnt[now]>1) --cnt[now],splay(now);
    else ch[R][0]=0;
}

void solve()
{
    int n;
    scanf("%d",&n);
    insert(0x3f3f3f3f);
    insert(0xcfcfcfcf);
    while (n--)
    {
        int opt,x;
        scanf("%d%d",&opt,&x);
        if (opt==1) insert(x);
        if (opt==2) remove(x);
        if (opt==3) printf("%d\n",Rank(x));
        if (opt==4) printf("%d\n",val[kth(x+1)]);
        if (opt==5) printf("%d\n",val[pre(x)]);
        if (opt==6) printf("%d\n",val[succ(x)]);
    }
}

int main()
{
    solve();
    return 0;
}

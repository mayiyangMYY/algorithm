#include <bits/stdc++.h>
using namespace std;
const int N=100005;
#define int long long
template <class T> void read(T &u)
{
    u=0; char c=getchar(); int flag=0;
    while (c<'0'||c>'9') flag|=(c=='-'),c=getchar();
    while (c>='0'&&c<='9') u=(u<<3)+(u<<1)+(c^48),c=getchar();
    if (flag) u=-u;
}

int n,m=1,q;
int sum[N<<2],add[N<<2];
void init()
{
	read(n); read(q);
	m=1; while (m<n+2) m<<=1;
	for (int i=1,x;i<=n;++i)
	{
		read(x);
		sum[m+i]=x;
	}
	for (int i=m-1;i>=1;--i)
	{
		sum[i]=sum[i<<1]+sum[i<<1|1];
	}
}

/*单点修改 
void update(int pos,int num)
{
	for (int i=N+pos;i;i>>=1) sum[i]+=num;
}

int query(int l,int r)
{
	int ans=0;
	for (int p=N+l-1,q=N+r+1;p^q^1;p>>=1,q>>=1)
	{
		if (~p&1) ans+=sum[p^1];
		if (q&1) ans+=sum[q^1];
	}
	return ans;
}
*/
void update(int x,int y,int num)
{
	int s=x-1+m,t=y+1+m,now=1;
	int totl=0,totr=0;
	for (;s^t^1;s>>=1,t>>=1,now<<=1)
	{
		sum[s]+=num*totl;
		sum[t]+=num*totr;
		if (~s&1) add[s^1]+=num,sum[s^1]+=num*now,totl+=now;
		if (t&1) add[t^1]+=num,sum[t^1]+=num*now,totr+=now;
	}	
	for (;s;s>>=1,t>>=1)
	{
		sum[s]+=num*totl;
		sum[t]+=num*totr;
	}
}

int query(int x,int y)
{
	int s=x-1+m,t=y+1+m,now=1;
	int totl=0,totr=0,ans=0;
	for (;s^t^1;s>>=1,t>>=1,now<<=1)
	{
		ans+=add[s]*totl;
		ans+=add[t]*totr;
		if (~s&1) ans+=sum[s^1],totl+=now;
		if (t&1) ans+=sum[t^1],totr+=now;
	}	
	for (;s;s>>=1,t>>=1)
	{
		ans+=add[s]*totl;
		ans+=add[t]*totr;
	}
	return ans;
}

void solve()
{
	int x,y,opt,k;
	while (q--)
	{
		read(opt); read(x); read(y);
		if (opt==1)
		{
			read(k);
			update(x,y,k);
		} 
		else 
		{
			printf("%lld\n",query(x,y));
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

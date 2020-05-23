#include <bits/stdc++.h>
using namespace std;
const int mod=998244353;  //998244353,1004535809,469762049 -> 3
const int N=4000002;
template <class T> void read(T &u)
{
    u=0; char c=getchar(); int flag=0;
    while (c<'0'||c>'9') flag|=(c=='-'),c=getchar();
    while (c>='0'&&c<='9') u=(u<<3)+(u<<1)+(c^48),c=getchar();
    if (flag) u=-u;
}
template <class T> void write(T u)
{
    if (u<0) printf("-"),u=-u;
    if (u<10) putchar(48+u);
    else write(u/10),putchar(48+u%10);
}
int n,m,rev[N];
int a[N],b[N];

int qpow(int a,int b)
{
	int ans=1;
	while (b)
	{
		if (b&1) ans=1LL*ans*a%mod;
		a=1LL*a*a%mod;
		b>>=1;
	}
	return ans;
}

void ntt(int *a,int n,int typ)
{
	for (int i=0;i<n;++i)
	{
		if (i<rev[i]) swap(a[i],a[rev[i]]);
	}
	for (int mid=1;mid<n;mid<<=1)
	{
		int wn=qpow(3,(mod-1)/(mid<<1)),x,y;
		if (typ==-1) wn=qpow(wn,mod-2);
		for (int i=0;i<n;i+=(mid<<1))
		{
			int w=1;
			for (int j=0;j<mid;++j,w=1LL*w*wn%mod)
			{
				x=a[i+j]; y=1LL*w*a[i+j+mid]%mod;
				a[i+j]=(x+y)%mod;
				a[i+j+mid]=(x-y+mod)%mod;
			}
		}
	}
}

int main()
{
	read(n); read(m);
	for (int i=0;i<=n;++i) read(a[i]);
	for (int i=0;i<=m;++i) read(b[i]);
	int len=1,cnt=-1;
	while (len<=m+n) len<<=1,++cnt;
	for (int i=0;i<len;++i)
	{
		rev[i]=rev[i>>1]>>1;
		if (i&1) rev[i]|=(1<<cnt);
	}
	ntt(a,len,1);
	ntt(b,len,1);
	for (int i=0;i<len;++i) a[i]=1LL*a[i]*b[i]%mod;
	ntt(a,len,-1);
	int tmp=qpow(len,mod-2);
	for (int i=0;i<=n+m;++i)
	{
		write(1LL*a[i]*tmp%mod); putchar(' ');
	}putchar('\n');
	return 0;
}

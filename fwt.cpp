#include <bits/stdc++.h>
using namespace std;
const int mod=998244353;
const int inv2=(mod+1)/2;
const int N=160000;
template <class T> void read(T &u)
{
    u=0; char c=getchar(); int flag=0;
    while (c<'0'||c>'9') flag|=(c=='-'),c=getchar();
    while (c>='0'&&c<='9') u=(u<<3)+(u<<1)+(c^48),c=getchar();
    if (flag) u=-u;
}
int n,tot;
int A[N],B[N],a[N],b[N];

void clear() {for (int i=0;i<tot;++i) a[i]=A[i],b[i]=B[i];}

void mul() {for (int i=0;i<tot;++i) a[i]=1LL*a[i]*b[i]%mod;}
void print() {for (int i=0;i<tot;++i) printf("%d%c",a[i]," \n"[i==tot-1]);}

void fwt_or(int *a,int n,int typ)
{
	for (int now=2,mid=1;now<=n;mid<<=1,now<<=1)
	{
		for (int i=0;i<n;i+=now)
		{
			for (int j=0;j<mid;++j)
			{
				if (typ==1) a[i+j+mid]=(a[i+j+mid]+a[i+j])%mod;
				else a[i+j+mid]=(a[i+j+mid]-a[i+j]+mod)%mod;	
			}
		}
	}
}

void fwt_and(int *a,int n,int typ)
{
	for (int now=2,mid=1;now<=n;mid<<=1,now<<=1)
	{
		for (int i=0;i<n;i+=now)
		{
			for (int j=0;j<mid;++j)
			{
				if (typ==1) a[i+j]=(a[i+j]+a[i+j+mid])%mod;
				else a[i+j]=(a[i+j]-a[i+j+mid]+mod)%mod;	
			}
		}
	}
}

void fwt_xor(int *a,int n,int typ)
{
	for (int now=2,mid=1;now<=n;mid<<=1,now<<=1)
	{
		for (int i=0;i<n;i+=now)
		{
			for (int j=0;j<mid;++j)
			{
				int x=a[i+j],y=a[i+j+mid];
				if (typ==1) 
				{
					a[i+j]=(x+y)%mod;
					a[i+j+mid]=(x-y+mod)%mod;
				}
				else
				{
					a[i+j]=1LL*(x+y)*inv2%mod;
					a[i+j+mid]=1LL*(x-y+mod)*inv2%mod;
				}	
			}
		}
	}
}

int main()
{
	read(n); tot=(1<<n);
	for (int i=0;i<tot;++i) read(A[i]);
	for (int i=0;i<tot;++i) read(B[i]);
	clear(); fwt_or(a,tot,1); fwt_or(b,tot,1); mul(); fwt_or(a,tot,-1); print();
	clear(); fwt_and(a,tot,1); fwt_and(b,tot,1); mul(); fwt_and(a,tot,-1); print();
	clear(); fwt_xor(a,tot,1); fwt_xor(b,tot,1); mul(); fwt_xor(a,tot,-1); print();
	return 0;
}

#include <bits/stdc++.h>
using namespace std;
const int N=4000010;
const double pi=acos(-1.0);
struct cp
{
	double x,y;
	cp(double a=0,double b=0){x=a,y=b;}
}a[N];
cp operator + (cp a,cp b) {return cp(a.x+b.x,a.y+b.y); }
cp operator - (cp a,cp b) {return cp(a.x-b.x,a.y-b.y); }
cp operator * (cp a,cp b) {return cp(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x); }
int n,m,rev[N]; 
/*void fft(cp *a,int n,int typ) //DFT:typ=1   IDFT:typ=-1
{
	if (n==1) return;
	cp a1[(n>>1)+1],a2[(n>>1)+1];
	for (int i=0;i<(n>>1);++i) a1[i]=a[i<<1],a2[i]=a[i<<1|1];
	fft(a1,n>>1,typ); fft(a2,n>>1,typ);
	cp wn(cos(2*pi/n),typ*sin(2*pi/n)),w(1,0);
	for (int i=0;i<(n>>1);++i,w=w*wn)
	{
		a[i]=a1[i]+w*a2[i];
		a[i+(n>>1)]=a1[i]-w*a2[i];
	}
}*/

void FFT(cp *a,int n,int typ) //DFT:typ=1   IDFT:typ=-1
{
	for (int i=0;i<n;++i)
	{
		if (i<rev[i]) swap(a[i],a[rev[i]]);
	}
	for (int mid=1;mid<n;mid<<=1)
	{
		cp wn(cos(pi/mid),typ*sin(pi/mid)),a1,a2;
		for (int i=0;i<n;i+=(mid<<1))
		{
			cp w(1,0);
			for (int j=0;j<mid;++j,w=w*wn)
			{
				a1=a[i+j],a2=w*a[i+j+mid];
				a[i+j]=a1+a2;
				a[i+j+mid]=a1-a2; 
			}
		}
	}
	if (typ==1) return;
	for (int i=0;i<n;++i) a[i].x/=n,a[i].y/=n; 
}

void init()
{
	scanf("%d%d",&n,&m);
	for (int i=0;i<=n;++i) scanf("%lf",&a[i].x);
	for (int i=0;i<=m;++i) scanf("%lf",&a[i].y);
}

void solve()
{
	int cnt=-1,len=1;
	while (len<=n+m) len<<=1,++cnt;
	for (int i=0;i<len;++i)
	{
		rev[i]=rev[i>>1]>>1;
		if (i&1) rev[i]|=(1<<cnt);
	}
	FFT(a,len,1);
	for (int i=0;i<len;++i)
		a[i]=a[i]*a[i];
	FFT(a,len,-1);
	for (int i=0;i<=n+m;++i)
	{
		printf("%d ",(int)(a[i].y/2+0.5));
	}printf("\n");
}

int main()
{
	init();
	solve();
	return 0;
}

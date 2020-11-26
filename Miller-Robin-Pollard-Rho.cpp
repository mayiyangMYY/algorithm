namespace PR
{
	unsigned seed=std::chrono::steady_clock::now().time_since_epoch().count();
	mt19937 my_rand(seed);
	ll n;
	map<ll,int> cnt;
	map<ll,int>::iterator it;
	inline ll ran(ll l,ll r){return my_rand()%(r-l+1)+l;}
	inline ll gcd(ll a,ll b){return b ? gcd(b,a%b) : a;}
	inline ll mabs(ll x){return x>0 ? x : -x;}
	inline ll mul(ll a,ll b,ll p){return ((a*b-(ll)((long double)a*b/p)*p+p)%p);}
	inline ll qpow(ll x,ll y,ll p)
	{
		ll ans=1;
		while (y)
		{
			if (y&1) ans=mul(ans,x,p);
			x=mul(x,x,p);
			y>>=1;
		}
		return ans;
	}

	inline bool mr(ll n,int t=50)
	{
		if (n==2||n==3) return 1;
		if (n<2||!(n&1)) return 0;
		ll num=n-1; int q=0;
		while (!(num&1)) num>>=1,++q;
		for (int i=1;i<=t;++i)
		{
			ll a=ran(2,n-2);
			ll x=qpow(a,num,n),y=0;
			for (int j=0;j<q;++j)
			{
				y=mul(x,x,n);
				if (y==1&&(x^1)&&(x^(n-1))) return 0;
				x=y;
			}
			if (y^1) return 0;
		}
		return 1;
	}

	inline ll f(ll x,ll c,ll p)
	{
		ll now=mul(x,x,p)+c;
		if (now>=p) now-=p;
		return now;
	}

	inline ll pr(ll n)
	{
		ll c=ran(1,n-1);
		ll A=0,B=0,val=1,d;
		int step=0,lim=1;
		for (;;lim<<=1,A=B,val=1)
		{
			for (step=1;step<=lim;++step)
			{
				B=f(B,c,n);
				val=mul(val,mabs(A-B),n);
				if (step%127==0)
				{
					d=gcd(val,n);
					if (d>1) return d;
				}
			}
			d=gcd(val,n);
			if (d>1) return d;
		}
	}

	inline void factor(ll n)
	{
		if (n==1) return;
		if (mr(n))
		{
			++cnt[n];
			return;
		}
		ll p=n;
		while (p>=n) p=pr(n);
		factor(p); factor(n/p);
	}

	void solve(ll x)
	{
		n=x; cnt.clear();
		if (mr(n))
		{
			printf("Prime\n");
			return;
		}
		else
		{
			factor(n);
			printf("%lld=",n);
			for (it=cnt.begin();it!=cnt.end();)
			{
				if (it->second==1) printf("%lld",it->first);
				else printf("%lld^%d",it->first,it->second);
				if ((++it)!=cnt.end()) printf("*");
			}printf("\n");
		}
	}
}

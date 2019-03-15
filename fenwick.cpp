单点修改 单点查询
int lowbit(int x)
{
	return x & (-x);
}

void update(int x,int num)
{
	for (int i=x; i<=n; i+=lowbit(i)) {
		tree[i]+=num;
	}
}

int query(int x)
{
	int ans=0;
	for (int i=x; i>0; i-=lowbit(i)) {
		ans+=tree[i];
	}
	return ans;
}

int main()
{
	scanf("%d%d",&n,&m)；
	while (m--) {
		scanf("%d%d%d",&x,&a,&b);
		if (x==1) {
			update(a,b);
		} else {
			printf("%d\n",query(b)-query(a-1));
		}
	}
	return 0;
}
-------------------------------------------------------------
区间修改 单点查询
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1; i<=n; ++i) {
		scanf("%d",&a[i]);
		update(i,a[i]-a[i-1]);
	}
	while (m--) {
		scanf("%d",&x);
		if (x==1) {
			scanf("%d%d%d",&u,&v,&k);
			update(u,k);
			update(v+1,-k);
		} else {
			scanf("%d",&u);
			printf("%d\n",query(u));
		}
	}
	return 0;
}
----------------------------------------------------------
区间修改 区间查询
ll n,k,x,C[2][N];
ll lowbit(ll x)
{
	return x & (-x);
}

void update(ll opt,ll pos,ll num)
{
	for (; pos<=n; pos+=lowbit(pos)) {
		C[opt][pos]+=num;
	}
}

ll query(ll opt,ll x)
{
	ll ans=0;
	for (; x>0; x-=lowbit(x)) {
		ans+=C[opt][x];
	}
	return ans;
}

ll query(ll x)
{
	return query(0,x)*(x+1)-query(1,x);
}

void solve()
{
	scanf("%s",opt);
	if (opt[0]=='Q') {
		scanf("%lld%lld",&x,&y);
		printf("%lld\n",query(y)-query(x-1));
	} else {
		scanf("%lld%lld%lld",&x,&y,&z);
		update(0,x,z);
		update(0,y+1,-z);
		update(1,x,x*z);
		update(1,y+1,(y+1)*(-z));
	}
}

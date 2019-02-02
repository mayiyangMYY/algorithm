单点修改
int n,a[N],mx[N<<2],sum[N<<2];
void push_up(int x)
{
	sum[x]=sum[x+x]+sum[x+x+1];
	mx[x]=max(mx[x+x],mx[x+x+1]);
}

void build(int x,int l,int r)
{
	if (l==r)
	{
		mx[x]=a[l];
		sum[x]=a[l];
		return;
	}
	int m=(l+r)>>1;
	build(x+x,l,m);
	build(x+x+1,m+1,r);
	push_up(x);
}

void modify(int x,int l,int r,int pos,int num)
{
	if (l==r)
	{
		sum[x]=num;
		mx[x]=num;
		return;
	}
	int m=(l+r)>>1;
	if (pos<=m) modify(x+x,l,m,pos,num);
	else modify(x+x+1,m+1,r,pos,num);
	push_up(x);
}

int query_max(int x,int l,int r,int L,int R)
{
	if (L<=l&&r<=R)
	{
		return mx[x];
	}
	int m=(l+r)>>1,ans=-inf;
	if (L<=m) ans=max(ans,query_max(x+x,l,m,L,R));
	if (R>m) ans=max(ans,query_max(x+x+1,m+1,r,L,R));
	return ans;
}

int query_sum(int x,int l,int r,int L,int R)
{
	if (L<=l&&r<=R)
	{
		return sum[x];
	}
	int m=(l+r)>>1,ans=0;
	if (L<=m) ans+=query_sum(x+x,l,m,L,R);
	if (R>m) ans+=query_sum(x+x+1,m+1,r,L,R);
	return ans;
}

区间修改
void push_up(int x)
{
	sum[x]=sum[x+x]+sum[x+x+1];
	mx[x]=max(mx[x+x],mx[x+x+1]);
}

void push_down(int x,int l,int m,int r)
{
	if (add[x])
	{
		add[x+x]+=add[x];
		add[x+x+1]+=add[x];
		sum[x+x]+=(m-l+1)*add[x];
		sum[x+x+1]+=(r-m)*add[x];
		mx[x+x]+=add[x];
		mx[x+x+1]+=add[x];
		add[x]=0;
	}
}

void build(int x,int l,int r)
{
	if (l==r)
	{
		mx[x]=a[l];
		sum[x]=a[l];
		return;
	}
	int m=(l+r)>>1;
	build(x+x,l,m);
	build(x+x+1,m+1,r);
	push_up(x);
}

void modify(int x,int l,int r,int L,int R,int num)
{
	if (L<=l&&r<=R)
	{
		add[x]+=num;
		sum[x]+=num*(r-l+1);
		mx[x]+=num;
		return;
	}
	int m=(l+r)>>1;
	push_down(x,l,m,r);
	if (L<=m) modify(x+x,l,m,L,R,num);
	if (R>m) modify(x+x+1,m+1,r,L,R,num);
	push_up(x);
}

int query_max(int x,int l,int r,int L,int R)
{
	if (L<=l&&r<=R)
	{
		return mx[x];
	}
	int m=(l+r)>>1,ans=-inf;
	push_down(x,l,m,r);
	if (L<=m) ans=max(ans,query_max(x+x,l,m,L,R));
	if (R>m) ans=max(ans,query_max(x+x+1,m+1,r,L,R));
	return ans;
}

int query_sum(int x,int l,int r,int L,int R)
{
	if (L<=l&&r<=R)
	{
		return sum[x];
	}
	int m=(l+r)>>1,ans=0;
	push_down(x,l,m,r);
	if (L<=m) ans+=query_sum(x+x,l,m,L,R);
	if (R>m) ans+=query_sum(x+x+1,m+1,r,L,R);
	return ans;
}

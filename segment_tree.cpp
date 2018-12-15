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

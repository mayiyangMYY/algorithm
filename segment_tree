void push_up(int x)
{
    mx[x]=max(mx[x+x],mx[x+x+1]);
}
void build(int x,int l,int r)
{
    if (l==r)
    {
        mx[x]=a[l];
        return;
    }
    int m=(l+r)>>1;
    build(x+x,l,m);
    build(x+x+1,m+1,r);
    push_up(x);
}
void modify(int x,int l,int r,int pos,int val)
{
    if (l==r)
    {
        mx[x]=val;
        return;
    }
    int m=(l+r)>>1;
    if (pos<=m) modify(x+x,l,m,pos,val);
    else modify(x+x+1,m+1,r,pos,val);
    push_up(x);
}
int query(int x,int l,int r,int L,int R)
{
    int m=(l+r)>>1,ans=0;
    if (L<=l&&r<=R) return mx[x];
    if (L<=m) ans=max(ans,query(x+x,l,m,L,R));
    if (R>m) ans=max(ans,query(x+x+1,m+1,r,L,R));
    return ans;
}

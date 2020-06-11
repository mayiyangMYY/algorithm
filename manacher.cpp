char s[N],s_new[N<<1];
int n,cnt,p[N<<1];
void init()
{
    scanf("%s",s);
    n=strlen(s);
    s_new[0]='$';
    s_new[1]='#';
    cnt=2;
    for (int i=0;i<n;++i)
    {
        s_new[cnt++]=s[i];
        s_new[cnt++]='#';
    }
    //printf("%s\n",s_new);
}

void solve()
{
    int ans=0;
    int mx=0,mid=0;
    for (int i=1;i<cnt;++i)
    {
        p[i]=i<mx ? _min(p[mid+mid-i],mx-i) : 1;
        while (s_new[i+p[i]]==s_new[i-p[i]]) ++p[i];
        if (i+p[i]>mx)
        {
            mid=i;
            mx=i+p[i];
        }
        checkmax(ans,p[i]-1);
    }
    printf("%d\n",ans);
}

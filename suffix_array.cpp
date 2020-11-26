namespace SA
{
	int n,alpha,top;
	int cnt[N],sa[N],rnk[N],rnk2[N],height[N];
	void build(char *s)
	{
		alpha=130;
		n=strlen(s+1);
		for (int i=1;i<=n;++i) ++cnt[s[i]],rnk[i]=s[i];
		for (int i=2;i<=alpha;++i) cnt[i]+=cnt[i-1];
		for (int i=n;i>=1;--i) sa[cnt[rnk[i]]--]=i;
		for (int len=1;len<=n;len<<=1)
		{
			top=0;
			for (int i=n-len+1;i<=n;++i) rnk2[++top]=i;
			for (int i=1;i<=n;++i) if (len<sa[i]) rnk2[++top]=sa[i]-len;
			memset(cnt,0,sizeof(int)*(alpha+1));
			for (int i=1;i<=n;++i) ++cnt[rnk[i]];
			for (int i=2;i<=alpha;++i) cnt[i]+=cnt[i-1];
			for (int i=n;i>=1;--i) sa[cnt[rnk[rnk2[i]]]--]=rnk2[i];
			alpha=0;
			for (int i=1;i<=n;++i)
			{
				if ((rnk[sa[i-1]]^rnk[sa[i]])||(rnk[sa[i-1]+len]^rnk[sa[i]+len])) ++alpha;
				rnk2[sa[i]]=alpha;
			}
			memcpy(rnk,rnk2,sizeof(int)*(n+1));
			if (alpha==n) break;
		}
		int tmp=0;
		for (int i=1;i<=n;++i)
		{
			if (tmp) --tmp;
			int j=sa[rnk[i]-1];
			while (s[i+tmp]==s[j+tmp]) ++tmp;
			height[rnk[i]]=tmp;
		}
	}
}

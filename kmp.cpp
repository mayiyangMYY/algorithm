void getnext(char *a)
{
	int i=0,j=-1,l=strlen(a);
	nxt[0]=-1;
	while (i<l)
	{
		if (j==-1||a[i]==a[j])
		{
			++i,++j;
			nxt[i]=j;
		}
		else
		{
			j=nxt[j];
		}
	}
}

void KMP(char *a,char *b)
{
	int i=0,j=0,A=strlen(a),B=strlen(b);
	while (i<A)
	{
		if (j==-1||a[i]==b[j])
		{
			++i,++j;
		}
		else j=nxt[j];
		if (j==B)
		{
			printf("%d\n",i-B+1);
			j=nxt[j];
		}
	}
}

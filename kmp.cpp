void get_common_suffix_prefix(char *p)
{
    int i=1,j=0;
    int len=strlen(p);
    for (;i<len;++i)
    {
        while (j&&p[i]!=p[j]) j=csp[j-1];
        if (p[i]==p[j]) ++j,csp[i]=j;
        else csp[i]=0;   
    }
}

//csp -> common_suffix_prefix
void kmp(char *s,char *t)
{
    int i=0,j=0;
    int S=strlen(s),T=strlen(t);
    for (;i<S;++i)
    {
        while (j&&s[i]!=t[j]) j=csp[j-1];
        if (s[i]==t[j]) ++j;
        if (j>=T)
        {
            int ans=i-j+1;
            printf("%d\n",ans);
            j=csp[j-1];
        }
    }
}

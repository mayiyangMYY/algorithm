#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int M=128;
const int N=100300;
int n,m,tot[M+15];
char str[N];
int sa[N],rnk[N],c[N][2],tmp[N];
void init()
{
    scanf("%s",str);
    n=strlen(str);
    for (int i=n;i>=1;--i) str[i]=str[i-1];  
    str[0]=' ';
}

void get_SA(char *str)
{
    memset(tot,0,sizeof(tot));
    for (int i=1;i<=n;++i) ++tot[str[i]];
    for (int i=1;i<=M;++i) tot[i]+=tot[i-1];
    for (int i=n;i>=1;--i)
    {
        sa[tot[str[i]]]=i;
        --tot[str[i]];
    } 
    for (int i=1;i<=n;++i)
    {
        rnk[sa[i]]=rnk[sa[i-1]];
        if (str[sa[i]]!=str[sa[i-1]]) ++rnk[sa[i]];
    }
    for (int len=1;len<=n;len<<=1)
    {
        memset(tot,0,sizeof(tot));
        for (int i=1;i<=n;++i)
        {
            c[i][0]=rnk[i],c[i][1]=rnk[i+len];
        }
        for (int i=1;i<=n;++i)
        {
            ++tot[c[i][1]];
        }
        for (int i=1;i<=M;++i) tot[i]+=tot[i-1];
        for (int i=n;i>=1;--i)
        {
            sa[tot[c[i][1]]]=i;
            --tot[c[i][1]];
        }
        for (int i=1;i<=n;++i)
        {
            rnk[sa[i]]=i;
        }
        memset(tot,0,sizeof(tot));
        for (int i=1;i<=n;++i)
        {
            ++tot[c[i][0]];
        }
        for (int i=1;i<=M;++i) tot[i]+=tot[i-1];
        for (int i=n;i>=1;--i)
        {
            tmp[tot[c[sa[i]][0]]]=sa[i];
            --tot[c[sa[i]][0]];
        }
        int flag=0;
        for (int i=1;i<=n;++i) sa[i]=tmp[i];
        for (int i=1;i<=n;++i)
        {
            rnk[sa[i]]=rnk[sa[i-1]];
            if (c[sa[i]][0]!=c[sa[i-1]][0]||c[sa[i]][1]!=c[sa[i-1]][1]) 
            {
                ++rnk[sa[i]];
                flag=1;
            }
        }
        if (!flag) break;
    }
    for (int i=1;i<=n;++i) cout<<rnk[i]<<" ";cout<<endl;
    for (int i=1;i<=n;++i) cout<<sa[i]<<" ";cout<<endl;
}

void get_height(char *str)
{
    
}

void solve()
{
    get_SA(str);
    get_height(str);
}

int main()
{
    init();
    solve();
    return 0;
}

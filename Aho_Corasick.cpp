//常规版AC自动机
int cnt=1;
struct node
{
    int ch[26],tag,fail;
}trie[N];

void insert(char *s)
{
    int len=strlen(s),now=1;
    for (int i=0;i<len;++i)
    {
        int dir=s[i]-'a';
        if (!trie[now].ch[dir]) 
        {
            ++cnt;
            trie[now].ch[dir]=cnt;   
        }
        now=trie[now].ch[dir];
    }
    trie[now].tag++;
}

void get_fail()
{
    for (int i=0;i<26;++i) trie[0].ch[i]=1;
    trie[1].fail=0;
    queue <int> q;
    q.push(1);
    while (!q.empty())
    {
        int now=q.front(); q.pop();
        for (int i=0;i<26;++i)
        {
            int to=trie[now].ch[i];
            if (!to)
            {
                trie[now].ch[i]=trie[trie[now].fail].ch[i];
            }
            else
            {
                trie[to].fail=trie[trie[now].fail].ch[i];
                q.push(to);
            }
        }
    }
}

int query(char *s)
{
    int now=1,len=strlen(s),ans=0;
    for (int i=0;i<len;++i)
    {
        int dir=s[i]-'a',tmp=trie[now].ch[dir];
        while (tmp>1&&trie[tmp].tag!=-1)
        {
            ans+=trie[tmp].tag;
            trie[tmp].tag=-1;
            tmp=trie[tmp].fail;
        }
        now=trie[now].ch[dir];
    }
    return ans;
}



//拓扑建图优化
void insert(char *s,int idx)
{
    int len=strlen(s),now=1;
    for (int i=0;i<len;++i)
    {
        int dir=s[i]-'a';
        if (!trie[now].ch[dir]) 
        {
            ++cnt;
            trie[now].ch[dir]=cnt;   
        }
        now=trie[now].ch[dir];
    }
    if (trie[now].tag) link[idx]=trie[now].tag;
    else trie[now].tag=idx,link[idx]=idx;
}

void get_fail()
{
    for (int i=0;i<26;++i) trie[0].ch[i]=1;
    trie[1].fail=0;
    queue <int> q;
    q.push(1);
    while (!q.empty())
    {
        int now=q.front(); q.pop();
        for (int i=0;i<26;++i)
        {
            int to=trie[now].ch[i];
            if (!to)
            {
                trie[now].ch[i]=trie[trie[now].fail].ch[i];
            }
            else
            {
                trie[to].fail=trie[trie[now].fail].ch[i];
                ++deg_in[trie[to].fail];
                q.push(to);
            }
        }
    }
}

void query(char *s)
{
    int now=1,len=strlen(s);
    for (int i=0;i<len;++i)
    {
        now=trie[now].ch[s[i]-'a'];
        ++trie[now].ans;
    }
}

void topo()
{
    queue <int> q;
    for (int i=1;i<=cnt;++i)
    {
        if (deg_in[i]==0)
            q.push(i);  
    }    
    while (!q.empty())
    {
        int now=q.front(); q.pop();
        ans[trie[now].tag]=trie[now].ans;
        int to=trie[now].fail;
        --deg_in[to];
        trie[to].ans+=trie[now].ans;
        if (!deg_in[to]) q.push(to);
    }
}

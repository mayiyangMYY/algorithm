#include <bits/stdc++.h>
using namespace std;
const int N=100005;
const int INF=500000000;
namespace Treap
{
	int n=0,root=0;
	struct node {
		int ch[2],val,pri,sz,cnt;
		node() {
		}
		node(int val):val(val) {
			sz=cnt=1;
			ch[0]=ch[1]=0;
			pri=rand();
		}
	} T[N];
	void update(int &now)
	{
		T[now].sz=T[T[now].ch[0]].sz+T[T[now].ch[1]].sz+T[now].cnt;
	}

	void rotate(int &now,int d)
	{
		int son=T[now].ch[d^1];
		T[now].ch[d^1]=T[son].ch[d];
		T[son].ch[d]=now;
		update(now),update(son);
		now=son;
	}

	void insert(int &now,int num)
	{
		if (!now) {
			now=++n;
			T[n]=node(num);
			return;
		}
		++T[now].sz;
		if (T[now].val==num) {
			++T[now].cnt;
			return;
		}
		int d=T[now].val<num;
		insert(T[now].ch[d],num);
		if (T[T[now].ch[d]].pri<T[now].pri) rotate(now,d^1);
	}

	void remove(int &now,int num)
	{
		if (!now) return;
		if (T[now].val==num) {
			if (T[now].cnt>1) {
				--T[now].cnt,--T[now].sz;
				return;
			}
			if (!T[now].ch[0] || !T[now].ch[1]) {
				now=T[now].ch[0]+T[now].ch[1];
				return;
			}
			int d=T[T[now].ch[0]].pri>T[T[now].ch[1]].pri;
			rotate(now,d^1);
			remove(now,num);
			return;
		}
		--T[now].sz;
		int d=num>T[now].val;
		remove(T[now].ch[d],num);
	}

	int rank(int now,int num)
	{
		if (!now) return 0;
		if (T[now].val==num) return T[T[now].ch[0]].sz+1;
		int d=T[now].val<num;
		if (d) return T[T[now].ch[0]].sz+T[now].cnt+rank(T[now].ch[1],num);
		return rank(T[now].ch[0],num);
	}

	int kth(int now,int k)
	{
		while (now) {
			if (T[T[now].ch[0]].sz>=k) {
				now=T[now].ch[0];
			} else if (T[T[now].ch[0]].sz+T[now].cnt<k) {
				k-=(T[T[now].ch[0]].sz+T[now].cnt);
				now=T[now].ch[1];
			} else return T[now].val;
		}
	}

	int pre(int now,int num)
	{
		if (!now) return -INF;
		if (num<=T[now].val) return pre(T[now].ch[0],num);
		else return max(pre(T[now].ch[1],num),T[now].val);
	}

	int post(int now,int num)
	{
		if (!now) return INF;
		if (num>=T[now].val) return post(T[now].ch[1],num);
		else return min(post(T[now].ch[0],num),T[now].val);
	}
}
using namespace Treap;
int main()
{
	int N;
	scanf("%d",&N);
	while (N--) {
		int opt,x;
		scanf("%d%d",&opt,&x);
		if (opt==1) insert(root,x);
		if (opt==2) remove(root,x);
		if (opt==3) printf("%d\n",rank(root,x));
		if (opt==4) printf("%d\n",kth(root,x));
		if (opt==5) printf("%d\n",pre(root,x));
		if (opt==6) printf("%d\n",post(root,x));
	}
	return 0;
}

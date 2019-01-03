#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define LS(n) node[(n)].ch[0]
#define RS(n) node[(n)].ch[1]

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

struct Splay {
	struct Node {
		int fa, ch[2];						//节点的父亲以及两个孩子 
		bool rev;							//翻转标记 
		int val, add, maxx, size;			//值，增加的延迟标记，最大值，子树的大小 
		void init(int _val) {
			val = maxx = _val;				//初始化最大值和值 
			size = 1;						//子树大小 
			add = rev = ch[0] = ch[1] = 0;	//初始化左右子树和延迟标记和反转标记 
		}
	} node[N];								//n个节点 
	int root;								//树根 

	void up(int n) {						//右节点向父亲更新 
		//这是求子树的最大值，树的最大值就是取树根，左子树，右子树三者中的最大值 
		node[n].maxx = max(node[n].val, max(node[LS(n)].maxx, node[RS(n)].maxx));
		//这是更新树根的大小，左子树+右子树+根 
		node[n].size = node[LS(n)].size + node[RS(n)].size + 1;
	}

	void down(int n) {						//区间增加的延迟标记往下传的操作 
		if (n == 0) return;					//空节点 
		if (node[n].add) {					//如果增加的延迟标记不为0 
			if (LS(n)) {					//如果分别有左右子树，就更新左右子树
				//标准的线段树区间操作的例子 
				node[LS(n)].val += node[n].add;
				node[LS(n)].maxx += node[n].add;
				node[LS(n)].add += node[n].add;
			}
			if (RS(n)) {
				node[RS(n)].val += node[n].add;
				node[RS(n)].maxx += node[n].add;
				node[RS(n)].add += node[n].add;
			}
			node[n].add = 0;				//增加延迟标记传下去了，自己的当然要赋值为0 
		}
		if (node[n].rev) {					//这是区间翻转的延迟标记 
			if (LS(n)) node[LS(n)].rev ^= 1;//翻转延迟标记往下传 
			if (RS(n)) node[RS(n)].rev ^= 1;
			swap(LS(n), RS(n));				//交换左右子树 
			node[n].rev = 0;				//翻转延迟标记设置为0 
		}
	}

	//左旋和右旋的合集 ，将节点n按照kind方式旋转 
	void rotate(int n, bool kind) {
		int fn = node[n].fa;
		int ffn = node[fn].fa;
		node[fn].ch[!kind] = node[n].ch[kind];
		node[node[n].ch[kind]].fa = fn;

		node[n].ch[kind] = fn;
		node[fn].fa = n;

		node[ffn].ch[RS(ffn) == fn] = n;
		node[n].fa = ffn;
		up(fn);
	}

	//将节点n伸展到goal的 位置去 
	void splay(int n, int goal) {
		while (node[n].fa != goal) {
			int fn = node[n].fa;
			int ffn = node[fn].fa;
			down(ffn); down(fn); down(n);
			bool rotate_n = (LS(fn) == n);
			bool rotate_fn = (LS(ffn) == fn);
			if (ffn == goal) rotate(n, rotate_n);
			else {
				if (rotate_n == rotate_fn) rotate(fn, rotate_fn);
				else rotate(n, rotate_n);
				rotate(n, rotate_fn);
			}
		}
		up(n);
		if (goal == 0) root = n;
	}

	//在树种找位置为pos的点，其实和二叉查找树里面找排名为pos的点的方式一样 
	int select(int pos) {
		int u = root;
		down(u);								//区间加和区级翻转延迟标记下传 
		while (node[LS(u)].size != pos) {		//左孩子的大小不等于pos 
			if (pos < node[LS(u)].size)			//如果pos在左孩子就往左孩子走 
				u = LS(u);
			else {								//pos在右孩子 
				pos -= node[LS(u)].size + 1;	//pos减去左孩子和根的大小 
				u = RS(u);						//往右孩子走 
			}
			down(u);							//延迟标记下传 
		}
		return u;
	}

	//查找l到r这个区间 
	int query(int L, int R) {
		//u节点就是找到的l-1的节点，v节点就是找到的r+1的节点 
		int u = select(L - 1), v = select(R + 1);
		//将u节点旋转到0的位置（根），将v节点旋转到u的位置，那么 
		splay(u, 0); splay(v, u);				//通过旋转操作把询问的区间聚集到根的右子树的左子树下
		return node[LS(v)].maxx;
	}

	//区间加操作 
	void update(int L, int R, int val) {
		//把区间调上来 
		int u = select(L - 1), v = select(R + 1);
		splay(u, 0); splay(v, u);
		//标准的区间加操作 
		node[LS(v)].val += val;
		node[LS(v)].maxx += val;
		node[LS(v)].add += val;					//延迟标记下传 
	}

	//区间翻转操作 
	void reverse(int L, int R) {
		//找区间 
		int u = select(L - 1), v = select(R + 1);
		splay(u, 0); splay(v, u);
		//翻转延迟标记置为1 
		node[LS(v)].rev ^= 1;
	}

	int build(int L, int R) {
		if (L > R) return 0;
		if (L == R) return L;
		int mid = (L + R) >> 1;
		int r_L, r_R;
		LS(mid) = r_L = build(L, mid - 1);
		RS(mid) = r_R = build(mid + 1, R);
		node[r_L].fa = node[r_R].fa = mid;
		up(mid);
		return mid;
	}

	void init(int n) {
		node[0].init(-INF); node[0].size = 0;
		node[1].init(-INF);
		node[n + 2].init(-INF);
		for (int i = 2; i <= n + 1; ++i)
			node[i].init(0);

		root = build(1, n + 2);
		node[root].fa = 0;

		node[0].fa = 0;
		LS(0) = root;
	}
} splay_tree;

int main() {
	FILE *fp = NULL;
	FILE *fop = NULL;
	fp = fopen("data.txt", "r");
	fop = fopen("out.txt", "w+");
	if (fp == NULL)
	{
		printf("data.txt file could not be found\n");
		getchar();
		return 0;
	}
	int n, m;
	fscanf(fp, "%d%d", &n, &m);
	splay_tree.init(n);								//初始化 
	for (int i = 0; i < m; ++i) {
		int op, l, r, v;
		fscanf(fp, "%d", &op);
		if (op == 1) {								//操作1，区间加 
			fscanf(fp, "%d%d%d", &l, &r, &v);
			splay_tree.update(l, r, v);				//l到r区间上面加上v 
		}
		else if (op == 2) {							//操作2，区间翻转 
			fscanf(fp, "%d%d", &l, &r);
			splay_tree.reverse(l, r);				//翻转l到r区间 
		}
		else {
			fscanf(fp, "%d%d", &l, &r);
			fprintf(fop, "%d\n", splay_tree.query(l, r));//查询l到r的最大值
		}
	}

	return 0;
}
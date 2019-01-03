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
		int fa, ch[2];						//�ڵ�ĸ����Լ��������� 
		bool rev;							//��ת��� 
		int val, add, maxx, size;			//ֵ�����ӵ��ӳٱ�ǣ����ֵ�������Ĵ�С 
		void init(int _val) {
			val = maxx = _val;				//��ʼ�����ֵ��ֵ 
			size = 1;						//������С 
			add = rev = ch[0] = ch[1] = 0;	//��ʼ�������������ӳٱ�Ǻͷ�ת��� 
		}
	} node[N];								//n���ڵ� 
	int root;								//���� 

	void up(int n) {						//�ҽڵ����׸��� 
		//���������������ֵ���������ֵ����ȡ�������������������������е����ֵ 
		node[n].maxx = max(node[n].val, max(node[LS(n)].maxx, node[RS(n)].maxx));
		//���Ǹ��������Ĵ�С��������+������+�� 
		node[n].size = node[LS(n)].size + node[RS(n)].size + 1;
	}

	void down(int n) {						//�������ӵ��ӳٱ�����´��Ĳ��� 
		if (n == 0) return;					//�սڵ� 
		if (node[n].add) {					//������ӵ��ӳٱ�ǲ�Ϊ0 
			if (LS(n)) {					//����ֱ��������������͸�����������
				//��׼���߶���������������� 
				node[LS(n)].val += node[n].add;
				node[LS(n)].maxx += node[n].add;
				node[LS(n)].add += node[n].add;
			}
			if (RS(n)) {
				node[RS(n)].val += node[n].add;
				node[RS(n)].maxx += node[n].add;
				node[RS(n)].add += node[n].add;
			}
			node[n].add = 0;				//�����ӳٱ�Ǵ���ȥ�ˣ��Լ��ĵ�ȻҪ��ֵΪ0 
		}
		if (node[n].rev) {					//�������䷭ת���ӳٱ�� 
			if (LS(n)) node[LS(n)].rev ^= 1;//��ת�ӳٱ�����´� 
			if (RS(n)) node[RS(n)].rev ^= 1;
			swap(LS(n), RS(n));				//������������ 
			node[n].rev = 0;				//��ת�ӳٱ������Ϊ0 
		}
	}

	//�����������ĺϼ� �����ڵ�n����kind��ʽ��ת 
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

	//���ڵ�n��չ��goal�� λ��ȥ 
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

	//��������λ��Ϊpos�ĵ㣬��ʵ�Ͷ������������������Ϊpos�ĵ�ķ�ʽһ�� 
	int select(int pos) {
		int u = root;
		down(u);								//����Ӻ�������ת�ӳٱ���´� 
		while (node[LS(u)].size != pos) {		//���ӵĴ�С������pos 
			if (pos < node[LS(u)].size)			//���pos�����Ӿ��������� 
				u = LS(u);
			else {								//pos���Һ��� 
				pos -= node[LS(u)].size + 1;	//pos��ȥ���Ӻ͸��Ĵ�С 
				u = RS(u);						//���Һ����� 
			}
			down(u);							//�ӳٱ���´� 
		}
		return u;
	}

	//����l��r������� 
	int query(int L, int R) {
		//u�ڵ�����ҵ���l-1�Ľڵ㣬v�ڵ�����ҵ���r+1�Ľڵ� 
		int u = select(L - 1), v = select(R + 1);
		//��u�ڵ���ת��0��λ�ã���������v�ڵ���ת��u��λ�ã���ô 
		splay(u, 0); splay(v, u);				//ͨ����ת������ѯ�ʵ�����ۼ�����������������������
		return node[LS(v)].maxx;
	}

	//����Ӳ��� 
	void update(int L, int R, int val) {
		//����������� 
		int u = select(L - 1), v = select(R + 1);
		splay(u, 0); splay(v, u);
		//��׼������Ӳ��� 
		node[LS(v)].val += val;
		node[LS(v)].maxx += val;
		node[LS(v)].add += val;					//�ӳٱ���´� 
	}

	//���䷭ת���� 
	void reverse(int L, int R) {
		//������ 
		int u = select(L - 1), v = select(R + 1);
		splay(u, 0); splay(v, u);
		//��ת�ӳٱ����Ϊ1 
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
	splay_tree.init(n);								//��ʼ�� 
	for (int i = 0; i < m; ++i) {
		int op, l, r, v;
		fscanf(fp, "%d", &op);
		if (op == 1) {								//����1������� 
			fscanf(fp, "%d%d%d", &l, &r, &v);
			splay_tree.update(l, r, v);				//l��r�����������v 
		}
		else if (op == 2) {							//����2�����䷭ת 
			fscanf(fp, "%d%d", &l, &r);
			splay_tree.reverse(l, r);				//��תl��r���� 
		}
		else {
			fscanf(fp, "%d%d", &l, &r);
			fprintf(fop, "%d\n", splay_tree.query(l, r));//��ѯl��r�����ֵ
		}
	}

	return 0;
}
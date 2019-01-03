#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>

using namespace std;

const int maxn = 100000 + 5;
int n, m;

struct Heap
{
	int l, r, fa, val, dis;
}t[maxn];

int finds(int x)
{
	return t[x].fa == -1 ? x : t[x].fa = finds(t[x].fa);
}

int merge(int x, int y)
{
	if (x == 0)  return y;					//如果为0的话，就说明是空子树，根节点当然就是另一节点了
	if (y == 0)  return x;
	if (t[y].val > t[x].val)  swap(x, y);	//始终往右子树进行插入
	t[x].r = merge(t[x].r, y);
	t[t[x].r].fa = x;
	if (t[t[x].l].dis < t[t[x].r].dis) swap(t[x].l, t[x].r);   //是否需要左右子树的对换，这样是为了右子树尽量短
	if (t[x].r == 0)  t[x].dis = 0;			//距离的重新分配
	else t[x].dis = t[t[x].r].dis + 1;
	return x;
}

int pop(int &root)
{
	int l = t[root].l;
	int r = t[root].r;
	t[root].l = t[root].r = t[root].dis = 0;
	t[root].fa = -1;
	t[l].fa = t[r].fa = -1;			//删除root根节点
	return merge(l, r);				//这样一来相当于分裂成了两棵子树，重新进行合并，最后返回值为合并后的根节点
}

int push(int x, int y)
{
	return merge(x, y);
}

int main()
{
	FILE *fp = NULL;
	FILE *op = NULL;
	fp = fopen("data.txt", "r");
	op = fopen("out.txt", "w+");
	if (fp == NULL)
	{
		printf("data.txt file could not be found\n");
		getchar();
		return 0;
	}
	fscanf(fp, "%d", &n);
	for (int i = 1; i <= n; i++)
	{
		t[i].l = t[i].r = t[i].dis = 0;
		t[i].fa = -1;
		fscanf(fp, "%d", &t[i].val);
	}
	fscanf(fp, "%d", &m);
	while (m--)
	{
		int a, b;
		fscanf(fp, "%d%d", &a, &b);
		int x = finds(a);
		int y = finds(b);
		if (x != y)
		{
			t[x].val /= 2;
			int xx = push(pop(x), x);
			t[y].val /= 2;
			int yy = push(pop(y), y);
			fprintf(op, "%d\n", t[merge(xx, yy)].val);
		}
		else fprintf(op, "-1\n");
	}
	return 0;
}

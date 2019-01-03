#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>

using namespace std;

int f[20001], m, n, p, x, y;

int find(int x)
{
	if (f[x] != x) f[x] = find(f[x]);	//如果一个人的老祖宗不是自己（即自己不是根节点），那么把
	return f[x];						//他的爸爸设为爸爸的爸爸，最后return f[x]；
}

void o(int a, int b) { f[b] = a; }		//把其中一个老祖宗的老祖宗设为另一个老祖宗

int main()
{
	FILE *fp = NULL;
	FILE *op = NULL;
	fp = fopen("data.txt", "r");
	op = fopen("file.txt", "w+");

	if (fp == NULL)
	{
		printf("data.txt file could not be found\n");
		getchar();
		return 0;
	}

	fscanf(fp, "%d%d", &n, &m);
	for (int i = 1; i <= n; i++) f[i] = i;	//先把每个人的老祖宗设为自己
	for (int i = 1; i <= m; i++)
	{
		fscanf(fp, "%d%d", &x, &y);
		int r = find(x), rr = find(y);		//r、rr分别为x、y的老祖宗
		if (r != rr) o(r, rr);				//o函数即把两个人的老祖宗设为亲戚
	}

	fscanf(fp, "%d", &p);
	for (int i = 1; i <= p; i++)
	{
		fscanf(fp, "%d%d", &x, &y);
		if (find(x) == find(y))
		{
			fprintf(op, "Yes\n");
		}
		else 
		{
			fprintf(op, "No\n");
		}
	}

	return 0;
}

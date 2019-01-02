#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <fstream>
#define inf 0x3f3f3f3f
using namespace std;
int in[60], h[60], tot = 0, n, m, g[60][2005], l[60], p[60], c[60], f[60][106][2005];
struct edge
{
	int y, ne, num;
}e[200005];
void Addedge(int x, int y, int v)
{
	tot++;
	e[tot].y = y;
	e[tot].ne = h[x];
	h[x] = tot;
	e[tot].num = v;
	in[y]++;
}
void dp(int x)
{
	if (!h[x])
	{
		l[x] = min(l[x], m / c[x]);
		for (int i = 0; i <= l[x]; i++)
		{
			for (int j = i; j <= l[x]; j++)
			{
				f[x][i][j*c[x]] = p[x] * (j - i);
			}
		}
		return;
	}
	l[x] = m;
	for (int i = h[x]; i; i = e[i].ne)
	{
		int y = e[i].y;
		dp(y);
		l[x] = min(l[x], l[y] / e[i].num);
		c[x] += e[i].num*c[y];
	}
	l[x] = min(l[x], m / c[x]);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= m; j++)
		{
			g[i][j] = -inf;
		}
	}
	g[0][0] = 0;
	for (int all = l[x]; all >= 0; all--)
	{
		int tot = 0;
		for (int i = h[x]; i; i = e[i].ne)
		{
			tot++;
			int y = e[i].y;
			for (int j = 0; j <= m; j++)
			{
				for (int k = 0; k <= j; k++)
				{
					g[tot][j] = max(g[tot][j], g[tot - 1][j - k] + f[y][all*e[i].num][k]);
				}
			}
		}
		for (int i = 0; i <= all; i++)
		{
			for (int k = 0; k <= m; k++)
			{
				f[x][i][k] = max(f[x][i][k], g[tot][k] + p[x] * (all - i));
			}
		}
	}
}
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
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= 105; j++)
		{
			for (int k = 0; k <= m; k++)
			{
				f[i][j][k] = -inf;
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		char ch;
		fscanf(fp, "%d", &p[i]);
		fscanf(fp, "%c", &ch);
		fscanf(fp, "%c", &ch);
		if (ch == 'B')
		{
			fscanf(fp, "%d%d", &c[i], &l[i]);
		}
		else
		{
			int k;
			fscanf(fp, "%d", &k);
			while (k--)
			{
				int y, v;
				fscanf(fp, "%d%d", &y, &v);
				Addedge(i, y, v);
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (!in[i])
		{
			dp(i);
			for (int j = 0; j <= m; j++)
			{
				for (int k = 0; k <= l[i]; k++)
				{
					ans = max(ans, f[i][k][j]);
				}
			}
			break;
		}
	}
	fprintf(op, "%d", ans);
	return 0;
}

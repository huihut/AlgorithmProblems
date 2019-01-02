#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int T, n;
int sum[510000];

struct node
{
	int pos, x;
}a[510000];
int b[510000];

bool cmp(node x, node y)
{
	return x.x < y.x;
}

void update(int pos, int val)
{
	while (pos <= n)
	{
		sum[pos] += val;
		pos += (pos&(-pos));
	}
}

int query(int pos)
{
	int rec = 0;
	while (pos > 0)
	{
		rec += sum[pos];
		pos -= (pos&(-pos));
	}
	return rec;
}

int main()
{
	FILE *fp = NULL;
	fp = fopen("data.txt", "r");
	if (fp == NULL)
	{
		printf("data.txt file could not be found\n");
		getchar();
		return 0;
	}

	long long nxs = 0;
	fscanf(fp, "%d", &n);
	memset(sum, 0, sizeof(sum));
	for (int i = 1, x; i <= n; i++)
	{
		fscanf(fp, "%d", &a[i].x);
		a[i].pos = i;
	}
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; i++)
	{
		b[a[i].pos] = i;
	}
	for (int i = 1; i <= n; i++)
	{
		update(b[i], 1);
		int temp = query(b[i]);
		nxs += b[i] - temp;
	}
	cout << nxs << endl;

	getchar();
	return 0;
}

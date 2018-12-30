#include<cstdio>

using namespace std;

int f[5001], m, n, p, x, y;

int find(int x)
{
	if (f[x] != x) f[x] = find(f[x]);	//���һ���˵������ڲ����Լ������Լ����Ǹ��ڵ㣩����ô��
	return f[x];						//���İְ���Ϊ�ְֵİְ֣����return f[x]��
}

void o(int a, int b) { f[b] = a; }		//������һ�������ڵ���������Ϊ��һ��������

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

	fscanf(fp, "%d%d", &n, &m);
	for (int i = 1; i <= n; i++) f[i] = i;	//�Ȱ�ÿ���˵���������Ϊ�Լ�
	for (int i = 1; i <= m; i++)
	{
		fscanf(fp, "%d%d", &x, &y);
		int r = find(x), rr = find(y);		//r��rr�ֱ�Ϊx��y��������
		if (r != rr) o(r, rr);				//o�������������˵���������Ϊ����
	}

	fscanf(fp, "%d", &p);
	for (int i = 1; i <= p; i++)
	{
		fscanf(fp, "%d%d", &x, &y);
		if (find(x) == find(y)) printf("Yes\n");//��Ҫ��һ��
		else printf("No\n");
	}

	getchar();
	return 0;
}
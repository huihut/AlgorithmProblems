#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<cstdio>

using namespace std;

int main() {
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
	vector<int> vec;
	vector<int>::iterator beg;

	int n, m, i, index;
	while (!feof(fp))
	{
		fscanf(fp, "%d%d", &n, &m);
		for (i = 1; i <= n; i++)
			vec.push_back(i);
		index = 0;
		while (n > 0) {
			beg = vec.begin();
			index = (index - 1 + m) % n;
			fprintf(op, "%d ", vec[index]);
			beg += index;
			if (beg != vec.end())
				vec.erase(beg);
			n--;
		}
	}
	
	return 0;
}

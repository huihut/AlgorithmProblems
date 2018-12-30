#include <stdio.h>

//通项法
int Neumann2_3_12(int n) {

	//通项公式的求解请查看说明文档
	return 2 * n*n + 2 * n + 1;
}

//递归法
int Neumann2_4_12(int n) {

	//由图可知第0次有1个方格
	if (n == 0) return 1;

	//递推关系的求解请查看说明文档
	return Neumann2_4_12(n - 1) + 4 * n;
}

int main() {
	int n, fun, a;

	printf("------冯诺依曼邻居问题------\n");
	printf("已知：\n");
	printf(" 0 阶冯诺依曼邻居的元胞数为 1 \n");
	printf(" 1 阶冯诺依曼邻居的元胞数为 5 \n");
	printf(" 2 阶冯诺依曼邻居的元胞数为 13 \n");
	printf("求：\n");
	printf(" n 阶冯诺依曼邻居的元胞数\n");
	printf("----------------------------\n");
	printf("请输入n\n");
	scanf("%d", &n);
	printf("【1】通项公式法\n");
	printf("【2】递归法\n");
	scanf("%d", &fun);

	switch (fun)
	{
	case 1:
		//用通项公式求解
		a = Neumann2_3_12(n);
		printf("------------通项法-------------\n");
		printf(" %d 阶冯诺依曼邻居的元胞数为 %d\n", n, a);
		break;
	case 2:
		//建立递推关系，使用递归求解
		a = Neumann2_4_12(n);
		printf("------------递归法-------------\n");
		printf(" %d 阶冯诺依曼邻居的元胞数为 %d\n", n, a);
		break;
	default:
		printf("输入错误！\n");
		break;
	}
	getchar();
	getchar();
	return 0;
}
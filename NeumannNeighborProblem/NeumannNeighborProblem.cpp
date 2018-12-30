#include <stdio.h>

//ͨ�
int Neumann2_3_12(int n) {

	//ͨ�ʽ�������鿴˵���ĵ�
	return 2 * n*n + 2 * n + 1;
}

//�ݹ鷨
int Neumann2_4_12(int n) {

	//��ͼ��֪��0����1������
	if (n == 0) return 1;

	//���ƹ�ϵ�������鿴˵���ĵ�
	return Neumann2_4_12(n - 1) + 4 * n;
}

int main() {
	int n, fun, a;

	printf("------��ŵ�����ھ�����------\n");
	printf("��֪��\n");
	printf(" 0 �׷�ŵ�����ھӵ�Ԫ����Ϊ 1 \n");
	printf(" 1 �׷�ŵ�����ھӵ�Ԫ����Ϊ 5 \n");
	printf(" 2 �׷�ŵ�����ھӵ�Ԫ����Ϊ 13 \n");
	printf("��\n");
	printf(" n �׷�ŵ�����ھӵ�Ԫ����\n");
	printf("----------------------------\n");
	printf("������n\n");
	scanf("%d", &n);
	printf("��1��ͨ�ʽ��\n");
	printf("��2���ݹ鷨\n");
	scanf("%d", &fun);

	switch (fun)
	{
	case 1:
		//��ͨ�ʽ���
		a = Neumann2_3_12(n);
		printf("------------ͨ�-------------\n");
		printf(" %d �׷�ŵ�����ھӵ�Ԫ����Ϊ %d\n", n, a);
		break;
	case 2:
		//�������ƹ�ϵ��ʹ�õݹ����
		a = Neumann2_4_12(n);
		printf("------------�ݹ鷨-------------\n");
		printf(" %d �׷�ŵ�����ھӵ�Ԫ����Ϊ %d\n", n, a);
		break;
	default:
		printf("�������\n");
		break;
	}
	getchar();
	getchar();
	return 0;
}
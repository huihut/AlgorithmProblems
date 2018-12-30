#include <iostream>
#include <algorithm>
using namespace std;

int *w = NULL;		// �洢ÿ����Ʒ����������ָ��
int *v = NULL;		// �洢ÿ����Ʒ��ֵ������ָ��
int **T = NULL;		// �洢���������������ָ��
int n;				// ��Ʒ����n
int W;				// �����ܳ���W

// ��������ֵ�����ֵ
int max(int a, int b)
{
	return (a > b) ? a : b;
}

// ������������ʾ��������ı��
void packIterative()
{
	// ѭ������n��
	for (int i = 1; i <= n; ++i)
	{
		// ѭ������W��
		for (int j = 1; j <= W; ++j)
		{
			//��i����Ʒ��װ�£���Ƚϰ�����i����Ʒ�Ͳ�������i����Ʒ��ȡ�����ֵ
			if (w[i] <= j)
				T[i][j] = max(v[i] + T[i - 1][j - w[i]], T[i - 1][j]);

			// ��i����Ʒ����װ�£���ݹ�װi-1��
			else
				T[i][j] = T[i - 1][j];
		}
	}
}

// �ݹ鷨����֧����ʾ��������ı��
int packRecursive(int i, int j, int *w, int *v)
{
	// ������������ʼ��������i����jΪ0ʱ����ܼ�ֵΪ0
	if (i == 0 || j == 0)
		return 0;

	// ��i����Ʒ����װ�£���ݹ�װi-1��
	if (w[i] > j)
		return packRecursive(i - 1, j, w, v);

	//��i����Ʒ��װ�£���Ƚϰ�����i����Ʒ�Ͳ�������i����Ʒ��ȡ�����ֵ
	else
		return max(v[i] + packRecursive(i - 1, j - w[i], w, v), packRecursive(i - 1, j, w, v));
}

// ��ӡ��������ı��
void printT(int n, int W)
{
	// ��ӡn��
	for (auto i = 0; i <= n; i++)
	{
		// ��ӡ����
		cout << i << ":\t";

		// ��ӡW��
		for (int w = 0; w <= W; w++)
		{
			cout << T[i][w] << "\t";
		}

		// ����
		cout << endl;
	}
}

int main()
{

	cout << "---------------- �������� ----------------" << endl;
	cout << "��������Ʒ�� n (n>=0) " << endl;

	// ���뱳����
	cin >> n;

	if (cin.fail() || n < 0)
	{
		cout << "����n����" << endl;
		system("pause");
		return 0;
	}

	cout << "�����뱳�������� W (W>=0) " << endl;

	// ���뱳��������
	cin >> W;

	if (cin.fail() || W < 0)
	{
		cout << "����W����" << endl;
		system("pause");
		return 0;
	}

	// ����ռ�
	// ��w��v����n+1��С
	w = new int[n + 1];
	v = new int[n + 1];

	// ��T����n+1�У�����ʼ��Ϊ0
	T = new int *[n + 1]();
	// ��T����W+1�У�����ʼ��Ϊ0
	for (auto i = 0; i <= n; i++)
	{
		T[i] = new int[W + 1]();
	}

	// ���뱳���������ͼ�ֵ
	for (auto i = 1; i <= n; i++)
	{
		cout << "������� " << i << " �������������ͼ�ֵ���ÿո������" << endl;
		cin >> w[i] >> v[i];
		if (cin.fail() || w[i] < 0 || v[i] < 0)
		{
			cout << "�������" << endl;
			system("pause");
			return 0;
		}
	}

	cout << "------------------------------------------------" << endl;
	cout << "��ѡ���㷨��" << endl;
	cout << "��1��������" << endl;
	cout << "��2���ݹ鷨" << endl;
	cout << "------------------------------------------------" << endl;

	int choose;

	// �����㷨��ѡ��
	cin >> choose;
	switch (choose)
	{
	case 1:
	{
		// ������������ʾ��������ı��
		packIterative();
		cout << "��װ����Ʒ������ֵΪ " << T[n][W] << endl;
		cout << "------------------------------------------------" << endl;
		printT(n, W);
		break;
	}
	case 2:
	{
		// �ݹ鷨����֧����ʾ��������ı��
		cout << "��װ����Ʒ������ֵΪ " << packRecursive(n, W, w, v) << endl;
		break;
	}
	default:
	{
		cout << "�������" << endl;
		break;
	}
	}

	cout << "------------------------------------------------" << endl;

	system("pause");
	return 0;
}

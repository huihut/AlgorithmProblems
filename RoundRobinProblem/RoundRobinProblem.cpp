#include <iostream>
#include <math.h>

using namespace std;

// ѭ�����ճ̰��ź�������
void MatchTable(int k, int n, int **table);

int main()
{
	int n = 0, k = 0;

	// �û�����
	cout << "---------------- ѭ�����ճ̰������� ----------------" << endl;
	cout << "������k(k>=0)������ n=(2^k) ��ѡ�ֵ�ѭ����" << endl;

	// ����kֵ
	cin >> k;

	// �ж��������ݺϷ��ԣ�������������Ƿ�Ϊ���֣�kֵ�Ƿ����0
	if (cin.fail() || k < 0)
	{
		cout << "����k����" << endl;
		system("pause");
		return 0;
	}

	// ��������ճ̱��С
	n = pow(2, k);

	// �����ճ̱�ռ�
	int **table = new int *[n + 1];
	for (int i = 0; i <= n; i++)
	{
		table[i] = new int[n + 1];
	}

	// ����ѭ�����ճ̰��ţ������ճ̱�
	MatchTable(k, n, table);

	// ��ʾ���
	cout << "------------------------------------------------" << endl;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cout << table[i][j] << "\t";
		}
		cout << endl;
	}
	cout << "------------------------------------------------" << endl;

	// ��ͣ�鿴���
	system("pause");

	// �ͷ��ڴ�
	for (int i = 0; i <= n; i++)
		delete[] table[i];
	delete[] table;

	// ָ���ÿ�
	table = NULL;

	return 0;
}

// ����ѭ�����ճ̰��ţ������ճ̱�
void MatchTable(int k, int n, int **table)
{
	// �����ճ̱��һ�е�ֵ
	for (int i = 1; i <= n; i++)
		table[1][i] = i;

	// ÿ��������ʼ���λ��
	int begin = 1;

	// �÷��η���separate�ݣ�ѭ�����
	for (int separate = 1; separate <= k; separate++)
	{
		// �ճ̱���л���
		n /= 2;

		// flagΪÿһС�ݵ��еı��
		for (int flag = 1; flag <= n; flag++)
		{
			// ������
			for (int i = begin + 1; i <= 2 * begin; i++)
			{
				// ������
				for (int j = begin + 1; j <= 2 * begin; j++)
				{
					// �����Ͻǵ�ֵ�������½�
					table[i][j + (flag - 1) * begin * 2] = table[i - begin][j + (flag - 1) * begin * 2 - begin];
					// �����Ͻǵ�ֵ�������½�
					table[i][j + (flag - 1) * begin * 2 - begin] = table[i - begin][j + (flag - 1) * begin * 2];
				}
			}
		}
		// �����ճ̱����һ�����ֽ������
		begin *= 2;
	}
}

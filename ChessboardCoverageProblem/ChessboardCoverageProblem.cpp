#include <iostream>
#include <math.h>
#include <cctype>

using namespace std;

int num_Now = 0;								// ��¼L�͹��Ʊ��
int **board = NULL;								// ����ָ��

// ��������
void ChessBoard(int num_BoardTopLeftRow, int num_BoardTopLeftColumn, int num_SpecialRow, int num_SpecialColumn, int boardSize);

int main() {

	int num_BoardTopLeftRow = 0,				// �������Ͻǵ��к�
		num_BoardTopLeftColumn = 0,				// �������Ͻǵ��к�
		num_SpecialRow = 0,						// ���ⷽ�����ڵ��к�
		num_SpecialColumn = 0,					// ���ⷽ�����ڵ��к�
		boardSize = 0,							// ���̴�С
		k = 0;									// ���ɵ�(2^k)*(2^k)�����������

	// �û�����
	cout << "---------------- ���̸������� ----------------" << endl;
	cout << "������k(k>=0)������(2^k)*(2^k)�����������" << endl;

	// ����kֵ
	cin >> k;

	// �ж��������ݺϷ��ԣ�������������Ƿ�Ϊ���֣�kֵ�Ƿ����0
	if (cin.fail() || k < 0)
	{
		cout << "����k����" << endl;
		system("pause");
		return 0;
	}

	// �������̴�С
	boardSize = pow(2, k);

	cout << "���������ⷽ�����ڵ��кź��кţ���0��ʼ���ÿո������" << endl;

	// �������ⷽ�����ڵ��кź��к�
	cin >> num_SpecialRow >> num_SpecialColumn;

	// �ж��������ݺϷ��ԣ�������������Ƿ�Ϊ���֣����ⷽ���к��к��Ƿ����0�����ⷽ���к��к��Ƿ񲻴������̴�С
	if (cin.fail() || num_SpecialRow < 0 || num_SpecialColumn < 0 || num_SpecialRow >= boardSize || num_SpecialColumn >= boardSize)
	{
		cout << "�����кŻ��кŴ���" << endl;
		system("pause");
		return 0;
	}

	// �������̿ռ�
	board = new int *[boardSize];
	for (auto i = 0; i < boardSize; i++)
	{
		board[i] = new int[boardSize];
	}

	// Ϊ���ⷽ�񸳳�ֵ0
	board[num_SpecialRow][num_SpecialColumn] = 0;

	//ִ�����̸��Ǻ���
	ChessBoard(num_BoardTopLeftRow, num_BoardTopLeftColumn, num_SpecialRow, num_SpecialColumn, boardSize);

	// ��ʾ���
	cout << "------------------------------------------------" << endl;
	for (auto i = 0; i < boardSize; i++)
	{
		for (auto j = 0; j < boardSize; j++)
		{
			cout << board[i][j] << "\t";
		}
		cout << endl;
	}
	cout << "------------------------------------------------" << endl;

	// ��ͣ�鿴���
	system("pause");

	// �ͷ��ڴ�
	for (int i = 0; i < boardSize; i++)
		delete[] board[i];
	delete[] board;

	// ָ���ÿ�
	board = NULL;

	return 0;
}

// ���̸��Ǻ���
void ChessBoard(int num_BoardTopLeftRow, int num_BoardTopLeftColumn, int num_SpecialRow, int num_SpecialColumn, int boardSize)
{
	// ���̴�СΪ1��ֱ�ӷ���
	if (boardSize == 1) return;

	int num = ++num_Now,			// L�͹��Ʊ��
		size = boardSize / 2;		// �ָ����̣����и�һ��Ϊ��

	// �������Ͻ�������
	if (num_SpecialRow < num_BoardTopLeftRow + size && num_SpecialColumn < num_BoardTopLeftColumn + size)
	{
		// �ݹ鸲�Ǻ������ⷽ���������
		ChessBoard(num_BoardTopLeftRow, num_BoardTopLeftColumn, num_SpecialRow, num_SpecialColumn, size);
	}
	else
	{
		// �ñ��Ϊnum��L�͹��Ƹ������½�
		board[num_BoardTopLeftRow + size - 1][num_BoardTopLeftColumn + size - 1] = num;

		// �ݹ鸲����������
		ChessBoard(num_BoardTopLeftRow, num_BoardTopLeftColumn, num_BoardTopLeftRow + size - 1, num_BoardTopLeftColumn + size - 1, size);
	}

	// �������Ͻ�������
	if (num_SpecialRow < num_BoardTopLeftRow + size && num_SpecialColumn >= num_BoardTopLeftColumn + size)
	{
		// �ݹ鸲�Ǻ������ⷽ���������
		ChessBoard(num_BoardTopLeftRow, num_BoardTopLeftColumn + size, num_SpecialRow, num_SpecialColumn, size);
	}
	else
	{
		// �ñ��Ϊnum��L�͹��Ƹ������½�
		board[num_BoardTopLeftRow + size - 1][num_BoardTopLeftColumn + size] = num;

		// �ݹ鸲����������
		ChessBoard(num_BoardTopLeftRow, num_BoardTopLeftColumn + size, num_BoardTopLeftRow + size - 1, num_BoardTopLeftColumn + size, size);
	}

	// �������½�������
	if (num_SpecialRow >= num_BoardTopLeftRow + size && num_SpecialColumn < num_BoardTopLeftColumn + size)
	{
		// �ݹ鸲�Ǻ������ⷽ���������
		ChessBoard(num_BoardTopLeftRow + size, num_BoardTopLeftColumn, num_SpecialRow, num_SpecialColumn, size);
	}
	else
	{
		// �ñ��Ϊnum��L�͹��Ƹ������Ͻ�
		board[num_BoardTopLeftRow + size][num_BoardTopLeftColumn + size - 1] = num;

		// �ݹ鸲����������
		ChessBoard(num_BoardTopLeftRow + size, num_BoardTopLeftColumn, num_BoardTopLeftRow + size, num_BoardTopLeftColumn + size - 1, size);
	}

	// �������½�������
	if (num_SpecialRow >= num_BoardTopLeftRow + size && num_SpecialColumn >= num_BoardTopLeftColumn + size)
	{
		// �ݹ鸲�Ǻ������ⷽ���������
		ChessBoard(num_BoardTopLeftRow + size, num_BoardTopLeftColumn + size, num_SpecialRow, num_SpecialColumn, size);
	}
	else
	{
		// �ñ��Ϊnum��L�͹��Ƹ������Ͻ�
		board[num_BoardTopLeftRow + size][num_BoardTopLeftColumn + size] = num;

		// �ݹ鸲����������
		ChessBoard(num_BoardTopLeftRow + size, num_BoardTopLeftColumn + size, num_BoardTopLeftRow + size, num_BoardTopLeftColumn + size, size);
	}
}

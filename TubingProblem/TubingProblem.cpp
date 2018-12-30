#include <iostream>
using namespace std;

// �;�y����ָ��
float * y = NULL;

// ��������
void quick_sort(int low, int high)
{
	if (low >= high)		// ������־
		return;
	int first = low;		// ��λ�±�
	int last = high;		// ��λ�±�
	float key = y[first];	// ���һ��Ϊ��׼

	while (first < last)
	{
		// ���ȵ�һ��С���Ƶ�ǰ��
		while (first < last && y[last] >= key)
			last--;
		if (first < last)
			y[first++] = y[last];

		// ���ȵ�һ������Ƶ�����
		while (first < last && y[first] <= key)
			first++;
		if (first < last)
			y[last--] = y[first];
	}
	// ��׼��λ
	y[first] = key;
	// ǰ��ݹ�
	quick_sort(low, first - 1);
	// ���ݹ�
	quick_sort(first + 1, high);
}

int main()
{
	int n;					// �;���
	float mid;				// y������м�λ�õ���
	float minDistance = 0;	// ���;������ܵ�֮��Ĺܵ������ܺ���Сλ��

	cout << "---------------- ���͹����� ----------------" << endl;
	cout << "�������;��� n (n>=0) " << endl;

	// �����;���
	cin >> n;

	// �ж��������ݺϷ��ԣ�������������Ƿ�Ϊ���֣�kֵ�Ƿ����0
	if (cin.fail() || n < 0)
	{
		cout << "����n����" << endl;
		system("pause");
		return 0;
	}

	// ����n��y����洢�ռ�
	y = new float[n];

	cout << "������ " << n << " ���;��� y ���꣨�ÿո������" << endl;

	// �����;��� y ����
	for (auto i = 0; i < n; i++)
	{
		cin >> y[i];
	}

	// �ж��������ݺϷ���
	if (cin.fail())
	{
		cout << "����y�������" << endl;
		system("pause");
		return 0;
	}

	// ���ÿ��������y���������������
	quick_sort(0, n - 1);

	// ����y������м�λ�õ���
	mid = y[n / 2];

	// ��������;��������͹ܵĳ���֮��
	for (auto i = 0; i < n; i++)
	{
		minDistance += abs(y[i] - mid);
	}

	// ��ʾ���
	cout << "------------------------------------------------" << endl;
	// �ж��;���ż������ͬ�����
	if (n & 1)
	{
		// nΪ������������λ��Ϊy����ĵ�n/2���;���y����
		cout << "���ܵ�������λ��Ϊ��y = " << mid << endl;
	}
	else
	{
		// nΪż����������λ��Ϊy������м������;���y���������
		cout << "���ܵ�������λ��Ϊ��y = [" << y[n / 2 - 1] << "," << mid << "]" << endl;
	}
	// ������;������ܵ�֮��Ĺܵ��ܳ���
	cout << "���;������ܵ�֮��Ĺܵ��ܳ���Ϊ��" << minDistance << endl;
	cout << "------------------------------------------------" << endl;

	// ��ͣ�鿴���
	system("pause");

	// �ͷ��ڴ�
	delete[] y;

	// ָ���ÿ�
	y = NULL;

	return 0;
}

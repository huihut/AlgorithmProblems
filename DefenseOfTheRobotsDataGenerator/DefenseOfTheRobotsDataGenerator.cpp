#include <iostream>
#include <random>
#include <fstream>
#include <string>
using namespace std;

/*

ħ�޵�ͼ DotR��Defense of the Robots�������������������

*/

int main()
{
	std::random_device r;
	std::default_random_engine e1(r());
	// �����������Χ
	std::uniform_int_distribution<int> n_range(1, 51);			// װ������n��Χ
	std::uniform_int_distribution<int> m_range(0, 2000);		// �����m��Χ
	std::uniform_int_distribution<int> low_range(1, 9);			// �ͼ�װ��������ֵ��Χ
	std::uniform_int_distribution<int> high_range(10, 99);		// �߼�װ��������ֵ��Χ
	std::uniform_int_distribution<int> level_range(0, 1);		// װ��AB�ȼ���Χ
	std::uniform_int_distribution<int> price_range(1, 100);		// ĳ�ͼ�װ���ĵ��۷�Χ
	std::uniform_int_distribution<int> maximum_range(1, 100);	// ӵ��ĳ�ͼ�װ�������������Χ
	std::uniform_int_distribution<int> c_range(2, 9);			// �ϳ�ĳ�߼�װ����Ҫ�ĵͼ�װ��������Χ
	std::uniform_int_distribution<int> c_kind_range(1, 9);		// �ϳ�ĳ�߼�װ����Ҫ��ĳ�ͼ�װ�����෶Χ
	std::uniform_int_distribution<int> c_num_range(1, 9);		// �ϳ�ĳ�߼�װ����Ҫ��ĳ�ͼ�װ��������Χ


	ofstream outfile("data.txt");
	if (outfile) {
		int n = n_range(e1);
		int m = m_range(e1);
		outfile << n << " " << m << " ";
		for (size_t i = 0; i < n; i++)
		{
			int level = level_range(e1);
			if (level == 0)		// 0 �ȼ�Ϊ B ����ͨװ��
			{
				int power = low_range(e1);
				int price = price_range(e1);
				int maximum = maximum_range(e1);
				outfile << power << " " << 'B' << " " << price << " " << maximum << " ";
			}
			else                // 1 �ȼ�Ϊ A ���߼�װ��
			{
				int power = high_range(e1);
				int c = c_range(e1);
				outfile << power << " " << 'A' << " " << c << " ";
				for (size_t i = 0; i < c; i++)
				{
					int c_kind = c_kind_range(e1);
					int c_num = c_num_range(e1);
					outfile << c_kind << " " << c_num << " ";
				}
			}
		}
		outfile.close();
	}
	else {
		cerr << "Cannot write data.txt file" << endl;
	}
	return 0;
}
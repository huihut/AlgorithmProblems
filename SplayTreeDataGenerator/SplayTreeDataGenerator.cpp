#include <iostream>
#include <random>
#include <fstream>
#include <string>
using namespace std;

/*
�����ս��ߡ���չ����SplayTree�������������������
*/

int main()
{
	std::random_device r;
	std::default_random_engine e1(r());
	// ���г���n �ķ�Χ�� [1, 20000] ֮��������
	std::uniform_int_distribution<int> n_range(1, 20000);
	// ��������m �ķ�Χ�� [1, 30000] ֮��������
	std::uniform_int_distribution<int> m_range(1, 30000);
	// ����ѡ��opt �ķ�Χ�� [1, 3] ֮��������
	std::uniform_int_distribution<int> opt_range(1, 3);
	// ����1�ӵ��� �ķ�Χ�� [1, 5000] ֮��������
	std::uniform_int_distribution<int> v_range(1, 5000);

	ofstream outfile("data.txt");
	if (outfile) {

		// ������� n
		int n = n_range(e1);
		// ������� m
		int m = m_range(e1);
		outfile << n << " " << m << " ";

		for (size_t i = 0; i < m; i++)
		{
			// �� n �����������һ��������
			std::uniform_int_distribution<int> l_range(1, n);
			int l = l_range(e1);
			// ʣ���������ȡֵΪ [1, n-������]
			int rrange = n - l;
			// ���������ȡֵ��Χ�����������һ��������
			std::uniform_int_distribution<int> r_range(0, rrange);
			// ������ȡ ������ + ��������䷶Χ�е�һ��
			int r = l + r_range(e1);

			// ������ɲ���ѡ��opt
			int opt = opt_range(e1);
			outfile << opt << " ";

			if (opt == 1)
			{
				int v = v_range(e1);
				outfile << l << " " << r << " " << v << " ";
			}
			else
			{
				outfile << l << " " << r << " ";
			}
		}
		outfile.close();
	}
	else {
		cerr << "Cannot write data.txt file" << endl;
	}
	return 0;
}
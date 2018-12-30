#include <iostream>
#include <random>
#include <fstream>
#include <string>
using namespace std;

/*

������monkey king�������������������

*/

int main()
{
	std::random_device r;
	std::default_random_engine e1(r());
	// ���� [1, 99999] ֮��������
	std::uniform_int_distribution<int> total_range(1, 99999);

	ofstream outfile("data.txt");
	if (outfile) {
		// n ֻ����
		int n = total_range(e1);
		outfile << n << " ";
		for (size_t i = 0; i < n; i++)
		{
			// ÿֻ���ӵ�����ֵΪ [1, 99999]
			outfile << total_range(e1) << " ";
		}

		// �������� m
		int m = total_range(e1);
		outfile << m << " ";
		// ���� [1, n] ֮��������
		std::uniform_int_distribution<int> monkey_range(1, n);
		for (size_t i = 0; i < m; i++)
		{
			// �����������ֻ����
			int mk1 = monkey_range(e1);
			int mk2 = monkey_range(e1);
			while (mk1 == mk2)
			{
				mk2 = monkey_range(e1);
			}
			outfile << mk1 << " " << mk2 << " ";
		}
		outfile.close();
	}
	else {
		cerr << "Cannot write data.txt file" << endl;
	}
	return 0;
}
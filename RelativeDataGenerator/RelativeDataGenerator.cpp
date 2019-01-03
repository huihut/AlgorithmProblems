#include <iostream>
#include <random>
#include <fstream>
#include <string>
using namespace std;

/*
亲戚（并查集）测试数据随机生成器
*/

int main()
{
	std::random_device r;
	std::default_random_engine e1(r());
	// 人数、亲戚对数 的随机数
	std::uniform_int_distribution<int> n_range(1, 10000);
	std::uniform_int_distribution<int> m_range(1, 15000);
	std::uniform_int_distribution<int> q_range(1, 15000);

	ofstream outfile("data.txt");
	if (outfile) {

		// 随机生成人数
		int people = n_range(e1);
		// 随机生成亲戚关系对数
		int pair = m_range(e1);
		outfile << people << " " << pair << " ";

		// 在 [1, 人数] 内随机生成亲戚关系
		std::uniform_int_distribution<int> people_range(1, people);

		// 随机生成 pair 对关系
		for (size_t i = 0; i < pair; i++)
		{
			int p1 = people_range(e1);
			int p2 = people_range(e1);
			while (p1 == p2)
			{
				p2 = people_range(e1);
			}
			outfile << p1 << " " << p2 << " ";
		}

		// 随机生成查询的关系对数
		int relationship = q_range(e1);
		outfile << relationship << " ";

		// 查询 relationship 对关系
		for (size_t i = 0; i < relationship; i++)
		{
			int r1 = people_range(e1);
			int r2 = people_range(e1);
			while (r1 == r2)
			{
				r2 = people_range(e1);
			}
			outfile << r1 << " " << r2 << " ";
		}

		outfile.close();
	}
	else {
		cerr << "Cannot write data.txt file" << endl;
	}
	return 0;
}
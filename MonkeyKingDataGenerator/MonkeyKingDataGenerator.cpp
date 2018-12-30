#include <iostream>
#include <random>
#include <fstream>
#include <string>
using namespace std;

/*

猴王（monkey king）测试数据随机生成器

*/

int main()
{
	std::random_device r;
	std::default_random_engine e1(r());
	// 生成 [1, 99999] 之间的随机数
	std::uniform_int_distribution<int> total_range(1, 99999);

	ofstream outfile("data.txt");
	if (outfile) {
		// n 只猴子
		int n = total_range(e1);
		outfile << n << " ";
		for (size_t i = 0; i < n; i++)
		{
			// 每只猴子的力量值为 [1, 99999]
			outfile << total_range(e1) << " ";
		}

		// 争吵次数 m
		int m = total_range(e1);
		outfile << m << " ";
		// 生成 [1, n] 之间的随机数
		std::uniform_int_distribution<int> monkey_range(1, n);
		for (size_t i = 0; i < m; i++)
		{
			// 争吵的随机两只猴子
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
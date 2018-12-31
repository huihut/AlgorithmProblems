#include <iostream>
#include <random>
#include <fstream>
#include <string>
using namespace std;

/*

魔兽地图 DotR（Defense of the Robots）测试数据随机生成器

*/

int main()
{
	std::random_device r;
	std::default_random_engine e1(r());
	// 生成随机数范围
	std::uniform_int_distribution<int> n_range(1, 51);			// 装备总数n范围
	std::uniform_int_distribution<int> m_range(0, 2000);		// 金币数m范围
	std::uniform_int_distribution<int> low_range(1, 9);			// 低级装备的力量值范围
	std::uniform_int_distribution<int> high_range(10, 99);		// 高级装备的力量值范围
	std::uniform_int_distribution<int> level_range(0, 1);		// 装备AB等级范围
	std::uniform_int_distribution<int> price_range(1, 100);		// 某低级装备的单价范围
	std::uniform_int_distribution<int> maximum_range(1, 100);	// 拥有某低级装备的最大数量范围
	std::uniform_int_distribution<int> c_range(2, 9);			// 合成某高级装备需要的低级装备种数范围
	std::uniform_int_distribution<int> c_kind_range(1, 9);		// 合成某高级装备需要的某低级装备种类范围
	std::uniform_int_distribution<int> c_num_range(1, 9);		// 合成某高级装备需要的某低级装备个数范围


	ofstream outfile("data.txt");
	if (outfile) {
		int n = n_range(e1);
		int m = m_range(e1);
		outfile << n << " " << m << " ";
		for (size_t i = 0; i < n; i++)
		{
			int level = level_range(e1);
			if (level == 0)		// 0 等级为 B 级普通装备
			{
				int power = low_range(e1);
				int price = price_range(e1);
				int maximum = maximum_range(e1);
				outfile << power << " " << 'B' << " " << price << " " << maximum << " ";
			}
			else                // 1 等级为 A 级高级装备
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
#include <iostream>
#include <random>
#include <fstream>
#include <string>
using namespace std;

/*
约瑟夫问题（Joseph Problem）测试数据随机生成器
*/

int main()
{
	std::random_device r;
	std::default_random_engine e1(r());
	// 序列长度n 的范围是 [1, 30000] 之间的随机数
	std::uniform_int_distribution<int> n_range(1, 30000);

	ofstream outfile("data.txt");
	if (outfile) {

		// 随机生成 人数n
		int n = n_range(e1);
		// 随机生成 间隔m
		int m = n_range(e1);
		outfile << n << " " << m << " ";
		
		outfile.close();
	}
	else {
		cerr << "Cannot write data.txt file" << endl;
	}
	return 0;
}
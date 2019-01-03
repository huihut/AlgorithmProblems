#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <random>
#include <fstream>

/*
逆序对（Reverse Pairs）测试数据随机生成器
*/

int myrandom(int i) { return std::rand() % i; }

int main() {
	std::ofstream outfile("data.txt");
	if (outfile)
	{
		std::srand(unsigned(std::time(0)));
		std::random_device r;
		std::default_random_engine e1(r());
		// 生成 [1, 50000] 之间的随机数
		std::uniform_int_distribution<int> total_range(1, 50000);

		int size = total_range(e1);
		outfile << size << " ";

		std::vector<int> myvector;
		myvector.reserve(size);

		// 初始化所有值
		for (int i = 1; i < size; ++i) myvector.push_back(i);

		// 使用内建随机生成器
		std::random_shuffle(myvector.begin(), myvector.end());

		// 使用自定义随机生成器
		std::random_shuffle(myvector.begin(), myvector.end(), myrandom);

		for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
			outfile << *it << " ";

		outfile.close();
	}
	else {
		std::cerr << "Cannot write data.txt file" << std::endl;
	}

	return 0;
}
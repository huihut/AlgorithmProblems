#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <random>
#include <fstream>

/*
����ԣ�Reverse Pairs�������������������
*/

int myrandom(int i) { return std::rand() % i; }

int main() {
	std::ofstream outfile("data.txt");
	if (outfile)
	{
		std::srand(unsigned(std::time(0)));
		std::random_device r;
		std::default_random_engine e1(r());
		// ���� [1, 50000] ֮��������
		std::uniform_int_distribution<int> total_range(1, 50000);

		int size = total_range(e1);
		outfile << size << " ";

		std::vector<int> myvector;
		myvector.reserve(size);

		// ��ʼ������ֵ
		for (int i = 1; i < size; ++i) myvector.push_back(i);

		// ʹ���ڽ����������
		std::random_shuffle(myvector.begin(), myvector.end());

		// ʹ���Զ������������
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
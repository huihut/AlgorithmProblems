#include <iostream>
#include <random>
#include <fstream>
#include <string>
using namespace std;

/*
Լɪ�����⣨Joseph Problem�������������������
*/

int main()
{
	std::random_device r;
	std::default_random_engine e1(r());
	// ���г���n �ķ�Χ�� [1, 30000] ֮��������
	std::uniform_int_distribution<int> n_range(1, 30000);

	ofstream outfile("data.txt");
	if (outfile) {

		// ������� ����n
		int n = n_range(e1);
		// ������� ���m
		int m = n_range(e1);
		outfile << n << " " << m << " ";
		
		outfile.close();
	}
	else {
		cerr << "Cannot write data.txt file" << endl;
	}
	return 0;
}
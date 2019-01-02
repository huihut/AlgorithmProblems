#include <iostream>
#include <random>
#include <fstream>
#include <string>
using namespace std;

/*
序列终结者、伸展树（SplayTree）测试数据随机生成器
*/

int main()
{
	std::random_device r;
	std::default_random_engine e1(r());
	// 序列长度n 的范围是 [1, 20000] 之间的随机数
	std::uniform_int_distribution<int> n_range(1, 20000);
	// 操作次数m 的范围是 [1, 30000] 之间的随机数
	std::uniform_int_distribution<int> m_range(1, 30000);
	// 操作选项opt 的范围是 [1, 3] 之间的随机数
	std::uniform_int_distribution<int> opt_range(1, 3);
	// 操作1加的数 的范围是 [1, 5000] 之间的随机数
	std::uniform_int_distribution<int> v_range(1, 5000);

	ofstream outfile("data.txt");
	if (outfile) {

		// 随机生成 n
		int n = n_range(e1);
		// 随机生成 m
		int m = m_range(e1);
		outfile << n << " " << m << " ";

		for (size_t i = 0; i < m; i++)
		{
			// 在 n 里面随机生成一个左区间
			std::uniform_int_distribution<int> l_range(1, n);
			int l = l_range(e1);
			// 剩下右区间的取值为 [1, n-左区间]
			int rrange = n - l;
			// 在右区间的取值范围里面随机生成一个右区间
			std::uniform_int_distribution<int> r_range(0, rrange);
			// 右区间取 左区间 + 随机右区间范围中的一个
			int r = l + r_range(e1);

			// 随机生成操作选项opt
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
#include <iostream>
#include <vector>
#include <functional>

int add(int i, int k)
{
	return i + k;
}
int subtract(int i, int k)
{
	return i - k;
}
int main()
{
	std::vector<std::function<int(int, int)>> ops;
	ops.emplace_back(add);
	ops.emplace_back(subtract);
	const int input1 = 123;
	const int input2 = 13;
	for (const auto& op : ops)
	{
		std::cout << op(input1, input2) << std::endl;
	}
	auto& op = ops[0]; std::cout << op(input1, input2) << std::endl;
	return 0;
}
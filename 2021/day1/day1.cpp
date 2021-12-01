#include <iostream>
#include <vector>

void PartOne(const std::vector<int>& vals)
{
	unsigned increased{ 0 };
	unsigned decreased{ 0 };
	unsigned noChange{ 0 };
	for (auto it = vals.cbegin(), prev = vals.cbegin();
		it != vals.cend(); prev = it, ++it)
	{
		if (*it > *prev)      ++increased;
		else if (*it < *prev) ++decreased;
		else                  ++noChange;
	}

	std::cout << "Increased: " << increased << '\n';
	std::cout << "Decreased: " << decreased << '\n';
	std::cout << "No change: " << noChange << '\n';
}

void PartTwo(const std::vector<int>& vals)
{
	std::vector<int> sumsOfThree;
	for (std::size_t i = 0; i < vals.size() - 2; ++i)
	{
		int sum = vals[i] + vals[i + 1] + vals[i + 2];
		sumsOfThree.push_back(sum);
	}

	PartOne(sumsOfThree);
}

int main(int argc, void** argv[])
{
	std::vector<int> input;
	int curVal;
	while (std::cin >> curVal)
	{
		input.push_back(curVal);
	}

	std::cout << "Part 1" << '\n';
	PartOne(input);

	std::cout << "===================" << '\n';

	std::cout << "Part 2" << '\n';
	PartTwo(input);

	return 0;
}
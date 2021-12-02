#include <iostream>
#include <vector>
#include <string>

struct Movement
{
	std::string direction{ "" };
	int value{ 0 };
};

std::istream&
operator>>(std::istream& in, Movement& m)
{
	in >> m.direction >> m.value;

	return in;
}

unsigned PartOne(const std::vector<Movement>& input)
{
	unsigned horizontal{ 0 };
	unsigned depth{ 0 };

	for (const auto& m : input)
	{
		if (m.direction == "forward")
			horizontal += m.value;
		else if (m.direction == "up")
			depth -= m.value;
		else if (m.direction == "down")
			depth += m.value;
	}

	return horizontal * depth;
}

unsigned PartTwo(const std::vector<Movement>& input)
{
	unsigned horizontal{ 0 };
	unsigned depth{ 0 };
	unsigned aim{ 0 };

	for (const auto& m : input)
	{
		if (m.direction == "forward")
		{
			horizontal += m.value;
			depth += aim * m.value;
		}
		else if (m.direction == "up")
		{
			aim -= m.value;
		}
		else if (m.direction == "down")
		{
			aim += m.value;
		}
	}

	return horizontal * depth;
}

int main(int argc, void** argv[])
{
	std::vector<Movement> input;
	Movement mov;
	while (std::cin >> mov)
	{
		input.push_back(mov);
	}

	std::cout << "P1: " << PartOne(input) << '\n';
	std::cout << "P2: " << PartTwo(input) << '\n';

	return 0;
}

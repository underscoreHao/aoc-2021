// This is just playing around with lambdas
// The idea came from the C# version I did which doesn't have any if/switch statements
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

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

int main(int argc, void** argv[])
{
	std::vector<Movement> input;
	Movement mov;
	while (std::cin >> mov)
	{
		input.push_back(mov);
	}

	unsigned horizontal{ 0 };
	unsigned depth{ 0 };

	auto forward = [&horizontal](int val)
	{
		horizontal += val;
	};

	auto up = [&depth](int val)
	{
		depth -= val;
	};

	auto down = [&depth](int val)
	{
		depth += val;
	};

	std::unordered_map<std::string, std::function<void(int)>> funcs;
	funcs.emplace("forward", forward);
	funcs.emplace("up", up);
	funcs.emplace("down", down);

	for (const auto& i : input)
	{
		funcs[i.direction](i.value);
	}

	std::cout << "P1: " << horizontal * depth << '\n';

	return 0;
}

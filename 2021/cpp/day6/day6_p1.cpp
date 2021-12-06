#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>


int main(int argc, void** argv[])
{
	std::ifstream input;
	input.open("input");

	int num;
	std::string line;
	std::vector<int> lanternfish;
	std::getline(input, line);
	std::stringstream ss(line);
	
	while (ss >> num)
	{
		lanternfish.push_back(num);
		if (ss.peek() == ',') ss.ignore();
	}

	input.close();

	const int days{ 80 };
	int dayCnt{ 1 };
	while (dayCnt <= days)
	{
		std::vector<int> newborns;
		for (auto& f : lanternfish)
		{
			if (f == 0)
			{
				newborns.push_back(8);
				f = 6;
				continue;
			}
			--f;
		}

		for (auto& b : newborns) lanternfish.push_back(b);
		++dayCnt;
	}

	std::cout << "Part 1: " << lanternfish.size() << '\n';

	return 0;
}

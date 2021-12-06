#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <deque>
#include <numeric>

int main(int argc, char** argv[])
{
	std::ifstream input;
	input.open("input");

	int num;
	std::string line;
	std::getline(input, line);
	std::stringstream ss(line);
	std::deque<long long> lanternfish(9, 0);
	
	while (ss >> num)
	{
		if (ss.peek() == ',') ss.ignore();

		++lanternfish[num];
	}

	input.close();

	const int days{ 256 };
	int dayCnt{ 1 };
	while (dayCnt <= days)
	{
		const long long zeroes = lanternfish.front();
		lanternfish.pop_front();
		lanternfish[6] += zeroes;
		lanternfish.push_back(zeroes);
		++dayCnt;
	}

	std::cout << "Part 2: " << std::accumulate(lanternfish.begin(), lanternfish.end(), long long{ 0 }) << '\n';

	return 0;
}

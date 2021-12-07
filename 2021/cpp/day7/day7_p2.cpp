#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>

int main(int argc, char** argv[])
{
	std::ifstream input;
	input.open("input");

	int num;
	std::string line;
	std::getline(input, line);
	std::stringstream ss(line);
	std::vector<int> crabs;
	
	while (ss >> num)
	{
		if (ss.peek() == ',') ss.ignore();

		crabs.push_back(num);
	}

	input.close();

	// int maxPos = *std::max_element(crabs.begin(), crabs.end());
	// int minPos = *std::min_element(crabs.begin(), crabs.end());
	auto [minPos, maxPos] = std::minmax_element(crabs.begin(), crabs.end());

	std::unordered_map<int, int> fuelFreq;

	for (const int& c : crabs)
	{
		for (int i = *minPos; i <= *maxPos; ++i)
		{
			auto dist = std::abs(c - i);
			for (int x = 0, j = dist; j >= 0; ++x, --j)
				fuelFreq[i] += x;
		}
	}

	auto it = std::min_element(std::begin(fuelFreq), std::end(fuelFreq),
		[](const auto& l, const auto& r) { return l.second < r.second; });

	std::cout << "Part 2: " << it->second << '\n';

	return 0;
}

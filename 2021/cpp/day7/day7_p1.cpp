#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

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
		for (int i = *minPos; i <= *maxPos; ++i)
			fuelFreq[i] += std::abs(c - i);

	auto it = std::min_element(std::begin(fuelFreq), std::end(fuelFreq),
		[](const auto& l, const auto& r) { return l.second < r.second; });

	std::cout << "Part 1: " << it->second << '\n';

	return 0;
}

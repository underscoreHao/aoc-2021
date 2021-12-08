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

	std::string line;
	std::vector<std::string> values;

	while (getline(input, line))
	{
		std::string delimiter = "|";
		std::string spaceDelimiter = " ";
		size_t pos = 0;
		std::string token;
		while ((pos = line.find(delimiter)) != std::string::npos) {
			token = line.substr(0, pos);
			line.erase(0, pos + delimiter.length());

			size_t pos1 = 0;
			while ((pos1 = line.find(spaceDelimiter)) != std::string::npos) {
				values.push_back(line.substr(0, pos1));
				line.erase(0, pos1 + spaceDelimiter.length());
			}
			values.push_back(line);
		}
	}
	
	input.close();

	int cnt{ 0 };
	for (const auto& v : values)
	{
		if (v.size() == 2) ++cnt;
		if (v.size() == 4) ++cnt;
		if (v.size() == 3) ++cnt;
		if (v.size() == 7) ++cnt;
	}

	std::cout << "Part 1: " << cnt << '\n';

	return 0;
}

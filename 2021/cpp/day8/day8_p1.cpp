#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <array>

struct Signal
{
	Signal() = default;
	Signal(std::string sig)
	{
		for (char c : sig)
		{
			const int offset = c - 'a';
			flags |= (1 << offset);
		}
	}

	int ActiveFlags() const { return std::popcount(flags); }

	unsigned char flags{ 0 };
};

struct Display
{
	Display(std::string line)
	{
		std::vector<std::string> vals;
		size_t pos{ 0 };
		std::string token;
		std::string delimiter = " ";
		while ((pos = line.find(delimiter)) != std::string::npos)
		{
			token = line.substr(0, pos);
			vals.push_back(token);
			line.erase(0, pos + delimiter.length());
		}
		vals.push_back(line);

		for (int sigIdx = 0; sigIdx < 10; ++sigIdx)
			signals[sigIdx] = Signal(vals[sigIdx]);

		for (int outIdx = 0; outIdx < 4; ++outIdx)
			outputs[outIdx] = Signal(vals[11 + outIdx]);
	}

	int UniqueDigitsInOutput() const
	{
		int count = 0;
		for (const auto& sig : outputs)
		{
			switch (sig.ActiveFlags()) 
			{
				case 2:
				case 3:
				case 4:
				case 7:
					++count;
					break;
				default:
					break;
			}
		}
		return count;
	}

	std::array<Signal, 10> signals;
	std::array<Signal, 4> outputs;
};

int main(int argc, char** argv[])
{
	std::ifstream input;
	input.open("input");

	std::string line;
	std::vector<Display> displays;

	while (getline(input, line))
		displays.push_back(line);
	
	input.close();

	int cnt = 0;
	for (const auto& d : displays)
		cnt += d.UniqueDigitsInOutput();

	std::cout << "Part 1: " << cnt << '\n';

	return 0;
}

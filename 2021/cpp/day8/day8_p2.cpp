#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <bitset>
#include <unordered_map>
#include <functional>

struct Signal
{
	Signal() = default;
	Signal(std::string sig)
	{
		for (char c : sig)
		{
			const int offset = c - 'a';
			segments.set(offset);
		}
	}

	int ActiveSegmentsCount() const { return segments.count(); }

	bool operator==(const Signal& other) const
	{
		return segments == other.segments;
	}

	bool operator!=(const Signal& other) const {
		return segments != other.segments;
	}

	Signal operator+(const Signal& other) const
	{
		Signal result(*this);
		result.segments |= other.segments;
		return result;
	}

	Signal operator-(const Signal& other) const
	{
		Signal result(*this);
		result.segments &= ~other.segments;
		return result;
	}

	bool Contains(const Signal& other) const
	{
		return (segments & other.segments) == other.segments;
	}

	std::bitset<7> segments;
};

struct SignalHasher
{
	std::size_t operator()(const Signal& k) const
	{
		return (std::hash<std::bitset<7>>()(k.segments));
	}
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
			switch (sig.ActiveSegmentsCount()) 
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

	int DisplayValue() const
	{
		std::array<Signal, 10> decodedSignals;
		std::vector<Signal> seg5, seg6;
		for (const auto& sig : signals) {
			switch (sig.ActiveSegmentsCount())
			{
				case 2:
					decodedSignals[1] = sig;
					break;
				case 3:
					decodedSignals[7] = sig;
					break;
				case 4:
					decodedSignals[4] = sig;
					break;
				case 5:
					seg5.push_back(sig);
					break;
				case 6:
					seg6.push_back(sig);
					break;
				case 7:
					decodedSignals[8] = sig;
					break;
				default:
					break;
			}
		}

		const Signal signalAbcdf = decodedSignals[4] + decodedSignals[7];
		for (const auto& sig : seg6)
		{
			if (sig.Contains(signalAbcdf))
				decodedSignals[9] = sig;
			else if (sig.Contains(decodedSignals[1]))
				decodedSignals[0] = sig;
			else 
				decodedSignals[6] = sig;
		}

		const Signal signalC = decodedSignals[8] - decodedSignals[6];
		for (const auto& sig : seg5)
		{
			if (sig.Contains(decodedSignals[1]))
				decodedSignals[3] = sig;
			else if (sig.Contains(signalC))
				decodedSignals[2] = sig;
			else
				decodedSignals[5] = sig;
		}

		std::unordered_map<Signal, int, SignalHasher> sigMap;
		for (int i = 0; i < 10; ++i)
			sigMap[decodedSignals[i]] = i;

		int displayVal = 0;
		for (const auto& outSig : outputs)
		{
			const auto val = sigMap.find(outSig);
			displayVal = displayVal * 10 + val->second;
		}

		return displayVal;
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
		cnt += d.DisplayValue();

	std::cout << "Part 2: " << cnt << '\n';

	return 0;
}


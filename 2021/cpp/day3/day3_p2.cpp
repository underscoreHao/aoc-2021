#include <iostream>
#include <vector>
#include <string>
#include <bitset>

const int BITS{ 12 };

unsigned long GetOxygenGeneratorRating(const std::vector<std::string>& in)
{
    std::vector<std::string> v = in;
    int cnt1{ 0 };
    int cnt0{ 0 };
    char flag;

    for (int i = 0; i < BITS; ++i) // Columns
    {
        if (v.size() == 1) break;

        cnt1 = 0;
        cnt0 = 0;
        for (std::size_t j = 0; j < v.size(); ++j) // Rows
        {
            if (v[j][i] == '1') ++cnt1;
            else                ++cnt0;
        }

        flag = cnt1 >= cnt0 ? '1' : '0';

        std::vector<std::string> tmp;
        for (std::size_t j = 0; j < v.size(); ++j) // Prepare next
        {
            if (v[j][i] == flag) tmp.push_back(v[j]);
        }

        v = tmp;
    }

    return std::bitset<BITS>(v.front()).to_ulong();
}

unsigned long GetCo2ScrubberRating(const std::vector<std::string>& in)
{
    std::vector<std::string> v = in;
    int cnt1{ 0 };
    int cnt0{ 0 };
    char flag;

    for (int i = 0; i < BITS; ++i) // Columns
    {
        if (v.size() == 1) break;

        cnt1 = 0;
        cnt0 = 0;
        for (std::size_t j = 0; j < v.size(); ++j) // Rows
        {
            if (v[j][i] == '1') ++cnt1;
            else                ++cnt0;
        }

        flag = cnt1 < cnt0 ? '1' : '0';

        std::vector<std::string> tmp;
        for (std::size_t j = 0; j < v.size(); ++j) // Prepare next
        {
            if (v[j][i] == flag) tmp.push_back(v[j]);
        }

        v = tmp;
    }

    return std::bitset<BITS>(v.front()).to_ulong();
}

int main(int argc, void** argv[])
{
    std::vector<std::string> input;
    std::string bNum;
    while (std::cin >> bNum)
    {
        input.push_back(bNum);
	}

    if (input.empty()) return EXIT_FAILURE;

    auto oxyRating = GetOxygenGeneratorRating(input);
    auto co2Rating = GetCo2ScrubberRating(input);

    std::cout << oxyRating * co2Rating << '\n';

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <bitset>

int main(int argc, void** argv[])
{
    const int BITS{ 12 };
    std::vector<int> ones(BITS, 0);
    std::vector<int> zeroes(BITS, 0);

    std::string bNum;
    while (std::cin >> bNum)
    {
        for (int i = 0; i < BITS; ++i)
        {
            if (bNum[i] == '1') ones[i]++;
            else                zeroes[i]++;
        }
    }

    std::string gamma{ "" };
    std::string epsilon{ "" };

    for (int i = 0; i < BITS; i++)
    {
        if (ones[i] > zeroes[i])
        {
            gamma += "1";
            epsilon += "0";
        }
        else
        {
            gamma += "0";
            epsilon += "1";
        }
    }

    std::cout << std::bitset<BITS>(gamma).to_ulong() * std::bitset<BITS>(epsilon).to_ulong() << '\n';

    return 0;
}

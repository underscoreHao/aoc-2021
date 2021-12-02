// This is just playing around with function pointers
// The idea came from the C# version I did which doesn't have any if/switch statements
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

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

unsigned horizontal{ 0 };
unsigned depth{ 0 };
unsigned aim{ 0 };

void Forward(int val) { horizontal += val; }
void Up(int val) { depth -= val; }
void Down(int val) { depth += val; }

int main(int argc, void** argv[])
{
    std::vector<Movement> input;
    Movement mov;
    while (std::cin >> mov)
    {
        input.push_back(mov);
    }

    using Func = void (*)(int);
    std::unordered_map<std::string, Func> funcs;
    funcs["forward"] = Forward;
    funcs["up"] = Up;
    funcs["down"] = Down;

    for (const auto& i : input)
    {
        funcs[i.direction](i.value);
    }

    std::cout << "P1: " << horizontal * depth << '\n';

    return 0;
}

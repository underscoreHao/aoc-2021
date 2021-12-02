var input = File.ReadLines(@"./input")
    .Select(x => x.Split(" "))
    .Select(x => Tuple.Create(x[0], int.Parse(x[1])))
    .ToList();

int horizontal = 0;
int depth = 0;
int aim = 0;
Dictionary<string, Action<int>> funcs = new();
funcs.Add("forward", foo =>
{
    horizontal += foo;
    depth += aim * foo;
});
funcs.Add("up", foo => aim -= foo);
funcs.Add("down", foo => aim += foo);

input.ForEach(x => funcs[x.Item1](x.Item2));

Console.WriteLine(horizontal * depth);

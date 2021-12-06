#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

struct Point
{
	int x;
	int y;
	
	bool operator==(const Point& p) const
	{
		return p.x == x && p.y == y;
	}
};

struct Line
{
	Point start;
	Point end;

	int MinX() const { return std::min(start.x, end.x); }
	int MaxX() const { return std::max(start.x, end.x); }
	int MinY() const { return std::min(start.y, end.y); }
	int MaxY() const { return std::max(start.y, end.y); }

	Line(Point s, Point e) : start{ s }, end{ e } {}
};

void MarkIntersections(std::vector<Line>& lines, std::vector<std::vector<int>>& table, bool withDiagonal)
{
	for (const auto& l : lines)
	{
		if (l.start.x == l.end.x) // Vertical
		{
			const int minY = l.MinY();
			const int maxY = l.MaxY();
			for (int y = minY; y <= maxY; ++y) {
				++table[l.start.x][y];
			}
			continue;
		}

		if (l.start.y == l.end.y) // Horizontal
		{
			const int minX = l.MinX();
			const int maxX = l.MaxX();
			for (int x = minX; x <= maxX; ++x) {
				++table[x][l.start.y];
			}
			continue;
		}

		if (withDiagonal)
		{
			const int minX = l.MinX();
			const int maxX = l.MaxX();
			const bool left = minX == l.start.x;
			const int startY = left ? l.start.y : l.end.y;
			const int endY = left ? l.end.y : l.start.y;
			const bool up = endY > startY;

			for (int i = 0; i <= (maxX - minX); ++i) {
				const int x = minX + i;
				const int y = startY + (up ? i : -i);
				++table[x][y];
			}
		}
	}
}

int main(int argc, void** argv[])
{
	std::ifstream input;
	input.open("input");

	std::string line;
	std::vector<Line> lines;
	int x1, y1, x2, y2;
	while (std::getline(input, line))
	{
		std::string arrow;
		char c;
		std::stringstream ss(line);
		ss >> x1 >> c >> y1 >> c >> c >> x2 >> c >> y2;

		Line seg{ Point{x1, y1}, Point{x2, y2} };
		
		lines.push_back(seg);
	}

	input.close();

	int maxX{0};
	int maxY{0};
	for (const auto& l : lines) {
		maxX = std::max(maxX, l.MaxX());
		maxY = std::max(maxY, l.MaxY());
	}

	std::vector<std::vector<int>> table(maxX + 1, std::vector<int>(maxY + 1, 0));

	MarkIntersections(lines, table, false);

	int count = 0;
	for (const auto& row : table) {
		count += std::count_if(row.begin(), row.end(),
			[](int val) { return val >= 2; });
	}
	
	std::cout << "Part 1: " << count << '\n';

	return 0;
}

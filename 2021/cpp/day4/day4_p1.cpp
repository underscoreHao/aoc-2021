#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using BoardRow = std::vector<std::pair<int, bool>>;
using Board = std::vector<BoardRow>;
using BingoBoards = std::vector<Board>;

std::vector<int> GetBingoInput(const std::string& line)
{
	int num{ 0 };
	std::vector<int> bingoInput;
	std::stringstream ss(line);
	while (ss >> num)
	{
		bingoInput.push_back(num);
		if (ss.peek() == ',') ss.ignore();
	}

	return bingoInput;
}


bool IsRowBingo(const Board& board)
{
	bool isBingo = false;
	for (const auto& row : board)
	{
		isBingo = true;
		for (const auto& n : row)
			if (!n.second) 
				isBingo = false;

		if (isBingo) return true;
	}
	return false;
}

bool IsColumnBingo(const Board& board)
{
	bool isBingo = false;
	for (size_t i = 0; i < board.front().size(); ++i)
	{
		isBingo = true;
		for (size_t j = 0; j < board.size(); ++j)
			if (!board[j][i].second)
				isBingo = false;

		if (isBingo) return true;
	}
	return false;
}

bool IsBingo(const Board& board)
{
	return IsRowBingo(board) || IsColumnBingo(board);
}

int GetBoardScore(const Board& board)
{
	int score{ 0 };
	for (const auto& row : board)
		for (const auto& n : row)
			if (!n.second) score += n.first;

	return score;
}

std::pair<int, Board&> FindWinningBoard(const std::vector<int>& bingoNumbers, BingoBoards& bingoBoards)
{
	for (const auto& n : bingoNumbers)
	{
		for (auto& board : bingoBoards)
		{
			for (auto& row : board)
				for (auto i = 0; i < row.size(); ++i)
					if (row[i].first == n)
						row[i].second = true;

			// Check board
			if (IsBingo(board))
				return std::pair<int, Board&>{ n, board };
		}
	}
}

int main(int argc, void** argv[])
{
	std::ifstream input;
	input.open("input");
	
	std::string line;
	std::getline(input, line);
	auto bingoNumbers = GetBingoInput(line);

	std::getline(input, line); // Discard the empty line after bingo input

	BingoBoards bingoBoards;
	Board board;

	const int boardSize{ 5 };
	int lineCnt{ 0 };
	while (std::getline(input, line))
	{
		if (!line.empty())
		{
			std::istringstream iss(line);
			int c1, c2, c3, c4, c5;
			iss >> c1 >> c2 >> c3 >> c4 >> c5;

			BoardRow row = 
			{ {c1, false}, {c2, false}, {c3, false}, {c4, false}, {c5, false} };

			board.push_back(row);

			++lineCnt;
			if (lineCnt == boardSize)
			{
				bingoBoards.push_back(board);
				board.clear();
				lineCnt = 0;
			}
		}
	}

	input.close();

	auto win = FindWinningBoard(bingoNumbers, bingoBoards);
	int sum = GetBoardScore(win.second);
	
	std::cout << "Final score: " << sum * win.first << '\n';

    return 0;
}

#include "gmspch.hpp"
#include "TicTacToeBoard.hpp"

namespace gms
{
	TicTacToeBoard::TicTacToeBoard()
		: Board()
	{
	}

	void TicTacToeBoard::print()
	{
		std::cout << "-------------" << "\n";

		size_t rowId, idx;
		for (rowId = 0; rowId < cells.size();)
		{
			std::cout << "| ";

			for (idx = rowId; idx < cells.size() / 3 + rowId; idx++)
			{
				char out;

				switch (cells.at(idx).ownerId)
				{
				case 1:
					out = 'X';
					break;
				case 2:
					out = 'O';
					break;
				default:
					out = ' ';
					break;
				}
				std::cout << out << " | ";
			}
			rowId = idx;
			std::cout << "\n";
		}
		std::cout << "-------------" << "\n";
	}

	bool TicTacToeBoard::applyMove(int32_t move, const Player& player)
	{
		if (context->currentState() == states::Running)
		{
			if (move < 0 || move > cells.size())
				return false;

			if (cells[move].ownerId == 0)
			{
				cells[move].cell.setTexture(&(player.sign));
				cells[move].ownerId = player.id;
				return true;
			}
		}
		return false;
	}
}

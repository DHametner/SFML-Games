#include "gmspch.hpp"
#include "ConnectFourBoard.hpp"

namespace gms
{
    ConnectFourBoard::ConnectFourBoard()
		: Board()
    {
    }

	void ConnectFourBoard::print()
	{
		std::cout << "-----------------------------" << "\n";
		std::cout << "| 1 | 2 | 3 | 4 | 5 | 6 | 7 |" << "\n";

		int32_t columnId, idx;
		for (columnId = 0; columnId < cells.size();)
		{
			std::cout << "| ";

			for (idx = columnId; idx < cells.size() / 6 + columnId; idx++)
			{
				char out;

				switch (cells.at(idx).ownerId)
				{
				case 1:
					out = 'R';
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
			columnId = idx;
			std::cout << "\n";
		}
		std::cout << "-----------------------------" << "\n";
	}


	bool ConnectFourBoard::applyMove(int32_t move, const Player& player)
	{
		if (context->currentState() == State::Running)
		{
			if (move < 0 || move > config.columns - 1)
				return false;

			int32_t idx;
			for (idx = (cells.size() - config.columns) + move; idx >= move; idx -= 7)
			{
				if (cells[idx].ownerId == 0)
				{
					cells[idx].cell.setTexture(&(player.sign));
					cells[idx].ownerId = player.id;
					return true;
				}
			}
		}
		return false;
	}
}

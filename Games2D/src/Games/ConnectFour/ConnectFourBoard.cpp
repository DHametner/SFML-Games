#include "gmspch.hpp"
#include "ConnectFourBoard.hpp"

namespace gms
{
    ConnectFourBoard::ConnectFourBoard()
		: Board()
    {
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

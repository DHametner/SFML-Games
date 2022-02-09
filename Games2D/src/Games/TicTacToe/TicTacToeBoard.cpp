#include "gmspch.hpp"
#include "TicTacToeBoard.hpp"

namespace gms
{
	TicTacToeBoard::TicTacToeBoard()
		: Board()
	{
	}

	bool TicTacToeBoard::applyMove(int32_t move, const Player& player)
	{
		if (context->currentState() == State::Running)
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

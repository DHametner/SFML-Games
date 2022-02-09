#pragma once

#include "gmspch.hpp"
#include "Core/Board.inl"

namespace gms
{
	class TicTacToeBoard : public Board<TICTACTOE_SIZE>
	{
	public:
		TicTacToeBoard();
		TicTacToeBoard(const TicTacToeBoard&) = default;
		virtual ~TicTacToeBoard() = default;

	public:
		bool applyMove(int32_t, const Player&) override;
	};
}

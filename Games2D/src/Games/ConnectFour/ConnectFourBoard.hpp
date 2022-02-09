#pragma once

#include "gmspch.hpp"
#include "Core/Game.hpp"
#include "Core/Board.inl"

namespace gms
{
	class ConnectFourBoard : public Board<CONNECTFOUR_SIZE>
	{
	public:
		ConnectFourBoard();
		ConnectFourBoard(const ConnectFourBoard&) = default;
		virtual ~ConnectFourBoard() = default;

	public:
		bool applyMove(int32_t, const Player&) override;
	};
}

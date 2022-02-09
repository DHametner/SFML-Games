#pragma once

#include "gmspch.hpp"
#include "Core/Game.hpp"
#include "TicTacToe/TicTacToeBoard.hpp"

namespace gms
{
	class TicTacToe : public Game
	{
	public:
		TicTacToe();
		TicTacToe(const TicTacToe&) = default;
		virtual ~TicTacToe() = default;

	public:
		void initialize() override;

		int32_t getPlayerMove() override;

		bool hasWon(int32_t) override;
	};
}


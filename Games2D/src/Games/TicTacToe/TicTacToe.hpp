#pragma once

#include "gmspch.hpp"
#include "Core/Game.hpp"
#include "TicTacToe/TicTacToeBoard.hpp"

namespace gms
{
	class TicTacToe : public Game
	{
	public:
		TicTacToe(bool);
		TicTacToe(const TicTacToe&) = default;
		virtual ~TicTacToe() = default;

	public:
		void initialize() override;

		bool hasWon(int32_t) override;

		std::list<int32_t> getValidMoves();

		int32_t evaluateScore();

		int32_t minMove();

		int32_t maxMove();

		int32_t minimax();

		int32_t getPlayerMove(int32_t) override;
	};
}


#pragma once

#include "gmspch.hpp"
#include "Core/Game.hpp"
#include "ConnectFour/ConnectFourBoard.hpp"

namespace gms
{
	class ConnectFour : public Game
	{
	public:
		ConnectFour(bool);
		ConnectFour(const ConnectFour&) = default;
		virtual ~ConnectFour() = default;

	public:
		void initialize() override;

		bool hasWon(int32_t) override;

		int32_t getComputerMove() override;

		int32_t getPlayerMove(int32_t) override;
	};
}

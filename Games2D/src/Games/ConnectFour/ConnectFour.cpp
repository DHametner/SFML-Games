#include "gmspch.hpp"
#include "ConnectFour.hpp"

namespace gms
{
	ConnectFour::ConnectFour(bool singleplayer)
		: Game(singleplayer)
	{
		config.columns = CONNECTFOUR_COLUMNS;
		config.rows    = CONNECTFOUR_ROWS;
		config.border  = 40.0f;
		config.name    = "ConnectFour";

		board = std::make_shared<ConnectFourBoard>();
		board->configure(config);

		initialize();
	}

	void ConnectFour::initialize()
	{
		Game::initialize();

		playerOne.sign.loadFromFile("../Games2D/res/connectfour/p1_red_circle.png");
		playerTwo.sign.loadFromFile("../Games2D/res/connectfour/p2_orange_circle.png");
	}

	bool ConnectFour::hasWon(int32_t playerId)
	{
		if (playerId < 1 || playerId > 2)
			return false;

		if (context->currentState() == State::Won)
			return true;

		if (context->currentState() == State::Running)
		{
			int32_t size = config.columns * config.rows;
			int32_t columnIdx = 0;
			int32_t rowIdx = 0;
			int32_t winCount = 0;

			// vetrical check
			int32_t column, idx;
			for (column = size - config.columns; column < size; column++)
			{
				winCount = 0;
				for (idx = column; idx >= columnIdx; idx -= 7)
				{
					(board->at(idx).ownerId == playerId) ? winCount++ : winCount = 0;

					if (winCount == 4)
						return true;
				}
				idx++;
			}

			// horizontal check
			int32_t rowId;
			for (rowId = size - config.columns; rowId >= 0; rowId -= 7)
			{
				winCount = 0;
				for (idx = rowId; idx < size - rowIdx; idx++)
				{
					(board->at(idx).ownerId == playerId) ? winCount++ : winCount = 0;

					if (winCount == 4)
						return true;
				}
				rowIdx += 7;
			}

			// forward diagonal check
			for (column = size / 2; column < size - (config.columns - 1) / 2; column += 7)
			{
				for (rowId = column; rowId < column + 4; rowId++)
				{
					winCount = 0;
					for (idx = rowId; idx >= rowId - 6 * 3; idx -= 6)
					{
						(board->at(idx).ownerId == playerId) ? winCount++ : winCount = 0;

						if (winCount == 4)
							return true;
					}
				}
			}

			// backward diagonal check
			for (column = size / 2 + (config.columns - 1); column < size; column += 7)
			{
				for (rowId = column; rowId > column - 4; rowId--)
				{
					winCount = 0;
					for (idx = rowId; idx >= rowId - 8 * 3; idx -= 8)
					{
						(board->at(idx).ownerId == playerId) ? winCount++ : winCount = 0;

						if (winCount == 4)
							return true;
					}
				}
			}
		}
		return false;
	}

	int32_t ConnectFour::getPlayerMove(int32_t playerId)
	{
		if (playerId < 1 || playerId > 2)
			return -1;

		if (isSingleplayer && playerId == 2)
			return 1000;//minimax();

		sf::Vector2i pos = sf::Mouse::getPosition(*window);

		int32_t dx = (int32_t)(pos.x - config.border / 2);
		int32_t x = (int32_t)(dx / (config.kCellWidth + config.border));

		return x;
	}
}
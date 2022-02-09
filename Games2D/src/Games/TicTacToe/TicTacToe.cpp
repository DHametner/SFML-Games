#include "gmspch.hpp"
#include "TicTacToe.hpp"

namespace gms
{
	TicTacToe::TicTacToe()
		: Game()
	{
		config.columns = TICTACTOE_COLUMNS;
		config.rows    = TICTACTOE_ROWS;
		config.border  = 40.0f;
		config.name    = "TicTacToe";

		board = std::make_unique<TicTacToeBoard>();
		board->configure(config);

		initialize();
	}

	void TicTacToe::initialize()
	{
		Game::initialize();

		playerOne.sign.loadFromFile("../Games2D/res/tictactoe/p1_red_cross.png");
		playerTwo.sign.loadFromFile("../Games2D/res/tictactoe/p2_blue_circle.png");
	}

	bool TicTacToe::hasWon(int32_t playerId)
	{
		if (playerId == NULL)
			return false;

		if (context->currentState() == State::Won)
			return true;

		if (context->currentState() == State::Running)
		{
			int32_t size = config.columns * config.rows;
			int32_t winCount = 0;

			// check vertical
			int32_t pos, idx;
			for (pos = 0; pos < config.rows; pos++)
			{
				winCount = 0;
				for (idx = pos; idx <= config.columns * 2 + pos; idx += 3)
				{
					board->at(idx).ownerId == playerId ? winCount++ : winCount = 0;

					if (winCount == 3) {
						context->changeState(State::Won);
						return true;
					}
				}
			}

			// check horizontal
			for (pos = 0; pos < size; pos += 3)
			{
				winCount = 0;
				for (idx = pos; idx < config.rows + pos; idx++)
				{
					board->at(idx).ownerId == playerId ? winCount++ : winCount = 0;

					if (winCount == 3) {
						context->changeState(State::Won);
						return true;
					}
				}
			}

			// forward diagonal check
			winCount = 0;
			for (pos = config.rows - 1; pos <= config.rows * 2; pos += 2)
			{
				board->at(pos).ownerId == playerId ? winCount++ : winCount = 0;

				if (winCount == 3) {
					context->changeState(State::Won);
					return true;
				}
			}

			// backward diagonal check
			winCount = 0;
			for (pos = 0; pos <= size - 1; pos += 4)
			{
				board->at(pos).ownerId == playerId ? winCount++ : winCount = 0;

				if (winCount == 3) {
					context->changeState(State::Won);
					return true;
				}
			}
		}
		return false;
	}

	int32_t TicTacToe::getPlayerMove()
	{
		sf::Vector2i pos = sf::Mouse::getPosition(*window);

		int32_t dx = (int32_t)(pos.x - config.border / 2);
		int32_t x = (int32_t)(dx / (config.kCellWidth + config.border));

		int32_t dy = (int32_t)(pos.y - config.border / 2);
		int32_t y = (int32_t)(dy / (config.kCellHeight + config.border));

		return y * config.columns + x;
	}
}
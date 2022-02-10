#include "gmspch.hpp"
#include "TicTacToe.hpp"

namespace gms
{
	TicTacToe::TicTacToe(bool singleplayer)
		: Game(singleplayer)
	{
		config.columns = TICTACTOE_COLUMNS;
		config.rows = TICTACTOE_ROWS;
		config.border = 40.0f;
		config.name = "TicTacToe";

		board = std::make_shared<TicTacToeBoard>();
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
		if (playerId < 1 || playerId > 2)
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

					if (winCount == 3)
						return true;
				}
			}

			// check horizontal
			for (pos = 0; pos < size; pos += 3)
			{
				winCount = 0;
				for (idx = pos; idx < config.rows + pos; idx++)
				{
					board->at(idx).ownerId == playerId ? winCount++ : winCount = 0;

					if (winCount == 3)
						return true;
				}
			}

			// forward diagonal check
			winCount = 0;
			for (pos = config.rows - 1; pos <= config.rows * 2; pos += 2)
			{
				board->at(pos).ownerId == playerId ? winCount++ : winCount = 0;

				if (winCount == 3)
					return true;
			}

			// backward diagonal check
			winCount = 0;
			for (pos = 0; pos <= size - 1; pos += 4)
			{
				board->at(pos).ownerId == playerId ? winCount++ : winCount = 0;

				if (winCount == 3)
					return true;
			}
		}
		return false;
	}

	std::list<int32_t> TicTacToe::getValidMoves()
	{
		std::list<int32_t> validMoves;

		for (int32_t idx = 0; idx < config.columns * config.rows; idx++)
		{
			if (board->at(idx).ownerId == 0)
				validMoves.push_back(idx);
		}
		return validMoves;
	}

	int32_t TicTacToe::evaluateScore()
	{
		if (hasWon(playerOne.id))
			return 10;
		else if (hasWon(playerTwo.id))
			return -10;
		return 0;
	}

	int32_t TicTacToe::minMove()
	{
		int32_t bestScore = 10;
		int32_t moveScore = evaluateScore();

		if (moveScore == 10 || moveScore == -10)
			return moveScore;

		std::list<int32_t> validMoves = getValidMoves();

		while (!validMoves.empty())
		{
			board->at(validMoves.front()).ownerId = playerOne.id;

			int32_t score = maxMove();

			if (score < bestScore)
				bestScore = score;
			board->at(validMoves.front()).ownerId = 0;
			validMoves.pop_front();
		}
		return bestScore;
	}

	int32_t TicTacToe::maxMove()
	{
		int32_t bestScore = -10;
		int32_t moveScore = evaluateScore();

		if (moveScore == 10 || moveScore == -10)
			return moveScore;

		std::list<int32_t> validMoves = getValidMoves();

		while (!validMoves.empty())
		{
			board->at(validMoves.front()).ownerId = playerTwo.id;

			int32_t score = minMove();

			if (score > bestScore)
				bestScore = score;
			board->at(validMoves.front()).ownerId = 0;
			validMoves.pop_front();
		}
		return bestScore;
	}

	int32_t TicTacToe::minimax()
	{
		std::vector<int32_t> bestMoves;
		int32_t bestScore = -10;

		std::list<int32_t> validMoves = getValidMoves();

		while (!validMoves.empty())
		{
			board->at(validMoves.front()).ownerId = playerTwo.id;
			int32_t score = minMove();

			if (score > bestScore)
			{
				bestScore = score;
				bestMoves.clear();
				bestMoves.push_back(validMoves.front());
			}
			else if (score == bestScore)
			{
				bestMoves.push_back(validMoves.front());
			}
			board->at(validMoves.front()).ownerId = 0;
			validMoves.pop_front();
		}
		std::random_device random;
		std::mt19937 mt(random());
		std::uniform_real_distribution<double_t> distrib(0.0, bestMoves.size());

		std::cout << bestMoves.size();
		return bestMoves[(size_t)distrib(random)];
	}

	int32_t TicTacToe::getPlayerMove(int32_t playerId)
	{
		if (playerId < 1 || playerId > 2)
			return -1;

		if (isSingleplayer && playerId == 2)
			return minimax();

		sf::Vector2i pos = sf::Mouse::getPosition(*window);

		int32_t dx = (int32_t)(pos.x - config.border / 2);
		int32_t x = (int32_t)(dx / (config.kCellWidth + config.border));

		int32_t dy = (int32_t)(pos.y - config.border / 2);
		int32_t y = (int32_t)(dy / (config.kCellHeight + config.border));

		return y * config.columns + x;
	}
}
#include "gmspch.hpp"
#include "Game.hpp"

namespace gms
{
	Game::Game(bool singleplayer)
		: isSingleplayer(singleplayer)
	{
		context = GameContext::getInstance();
	}

	void Game::initialize()
	{
		sf::VideoMode videoMode;
		videoMode.width = (float_t)((config.columns + 1) * config.border + config.columns * config.kCellWidth);
		videoMode.height = (float_t)((config.rows + 1) * config.border + config.rows * config.kCellHeight);

		window = std::make_unique<sf::RenderWindow>(videoMode, config.name, sf::Style::Titlebar | sf::Style::Close);

		playerOne.id = 1;
		playerOne.name = "Player One";

		playerTwo.id = 2;
		playerTwo.name = isSingleplayer ? "Computer Player" : "Player Two";

		context->changeState(State::Running);
	}

	void Game::performMove(const Player* player)
	{
		while (!board->applyMove(getPlayerMove(player->id), *player));

		update();

		if (board->isFull())
			context->changeState(State::Full);
		else if (hasWon(player->id))
			context->changeState(State::Won);
	}

	void Game::update()
	{
		window->clear();

		float_t yPos = 0.0f;
		float_t xPos = 0.0f;

		//draw grid
		int32_t columId = 0;
		for (int32_t rowIdx = 0; rowIdx < config.rows; rowIdx++)
		{
			int32_t idx;
			for (idx = columId; idx < config.columns + config.columns * rowIdx; idx++)
			{
				if ((idx - columId) == 0)
					xPos = config.border + (idx - columId) * config.kCellSize.x;
				else
					xPos = config.border + config.border * (idx - columId) + (idx - columId) * config.kCellSize.x;

				if (rowIdx == 0)
					yPos = config.border + rowIdx * config.kCellSize.y;
				else
					yPos = config.border + config.border * rowIdx + rowIdx * config.kCellSize.y;

				board->at(idx).cell.setSize(config.kCellSize);
				board->at(idx).cell.setOutlineColor(sf::Color(0xB8B8B8B8));
				board->at(idx).cell.setOutlineThickness(config.border);
				board->at(idx).cell.setPosition(xPos, yPos);

				window->draw(board->at(idx).cell);
			}
			columId = idx;
		}
		window->display(); //window display
	}

	void Game::run()
	{
		Player* currentPlayer = &playerOne;

		int32_t count = 0;
		while (window->isOpen())
		{
			update(); //initial window update

			sf::Event event;
			while (window->waitEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window->close();
					break;

				case sf::Event::MouseButtonPressed:
					if (context->currentState() == State::Running)
					{
						performMove(currentPlayer);

						if (isSingleplayer && context->currentState() == State::Running) {
							using namespace std::this_thread;     // sleep_for, sleep_until
							using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
							using std::chrono::system_clock;

							sleep_for(150ms);
							performMove(&playerTwo);
						}
						else
						{
							if (currentPlayer->id == 1)
								currentPlayer = &playerTwo;
							else
								currentPlayer = &playerOne;
						}
					}
					break;
				default:
					break;
				}
			}
		}
	}

	GameContext* GameContext::instance = nullptr;

	GameContext* GameContext::getInstance()
	{
		if (instance == nullptr)
			instance = new GameContext;
		return instance;
	}

	bool GameContext::destroyInstance()
	{
		if (instance == nullptr)
			return false;

		std::free(instance);
		return true;
	}

	void GameContext::changeState(const State& state)
	{
		switch (m_state)
		{
		case State::Running:
		case State::Unknown:
			m_state = state;
			break;
		case State::Full:
		case State::Won:
			if (m_state == State::Full)
				m_state = state;
			break;
		default:
			break;
		}
	}

	State GameContext::currentState()
	{
		return m_state;
	}
}
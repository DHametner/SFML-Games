#include "gmspch.hpp"
#include "Game.hpp"

namespace gms
{
	Game::Game()
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
		playerTwo.name = "Player Two";

		context->changeState(State::Running);
	}

	void Game::update()
	{
		window->clear();

		float_t yPos = 0.0f;
		float_t xPos = 0.0f;

		//draw grid
		int32_t columID = 0;
		for (int32_t rowIdx = 0; rowIdx < config.rows; rowIdx++)
		{
			int32_t idx;
			for (idx = columID; idx < config.columns + config.columns * rowIdx; idx++)
			{
				if ((idx - columID) == 0)
					xPos = config.border + (idx - columID) * config.kCellSize.x;
				else
					xPos = config.border + config.border * (idx - columID) + (idx - columID) * config.kCellSize.x;

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
			columID = idx;
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

					if (board->applyMove(getPlayerMove(), *currentPlayer))
					{
						update();

						if (board->isFull())
							context->changeState(State::Full);
						else if (hasWon(currentPlayer->id))
							context->changeState(State::Won);
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
		if (instance == NULL)
			instance = new GameContext;
		return instance;
	}

	bool GameContext::destroyInstance()
	{
		if (instance == NULL)
			return false;

		std::free(instance);
		return true;
	}

	void GameContext::changeState(const State& state)
	{
		switch (m_state)
		{
		case State::Running:
		case State::Full:
		case State::Unknown:
			m_state = state;
			break;
		case State::Won:
		default:
			break;
		}
	}
	
	State GameContext::currentState()
	{
		return m_state;
	}
}
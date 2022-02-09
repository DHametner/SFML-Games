#pragma once

#include "gmspch.hpp"
#include "Basegame2D.hpp"

namespace gms
{
	class GameContext 
	{
	protected:
		static GameContext* instance;

	private:
		State m_state = State::Unknown;

	private:
		GameContext() = default;
		virtual ~GameContext() = default;

	public:
		static GameContext* getInstance();

		static bool destroyInstance();

		void changeState(const State&);

		State currentState();
	};

	class Game : public IGame2D
	{
	protected:
		GameContext* context;
		Player       playerOne;
		Player       playerTwo;

		std::unique_ptr<IBoard2D>         board;
		std::unique_ptr<sf::RenderWindow> window;
	public:
		Game();
		virtual ~Game() = default;

	private:
		void update();

	public:
		virtual void initialize();

		void run() override;
	};
}
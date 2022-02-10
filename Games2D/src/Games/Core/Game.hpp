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
		bool		 isSingleplayer;

		std::shared_ptr<IBoard2D>         board;
		std::unique_ptr<sf::RenderWindow> window;
	public:
		Game(bool);
		virtual ~Game() = default;

		void performMove(const Player*);

		void update();

	public:
		virtual void initialize();

		void run() override;
	};
}
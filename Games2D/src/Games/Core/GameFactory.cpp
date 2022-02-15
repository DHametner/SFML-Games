#include "gmspch.hpp"
#include "GameFactory.hpp"
#include "Games2D.hpp"

namespace gms
{
	IGame2D* GameFactory::createGame(const types::type_t& type, bool singleplayer)
	{
		IGame2D* game = nullptr;

		switch (type)
		{
		case types::TicTacToe:
			game = new TicTacToe(singleplayer);
			break;
		case types::ConnectFour:
			game = new ConnectFour(singleplayer);
			break;	
		case types::Unknown:
		default:
			break;
		}
		return game;
	}

	bool GameFactory::destroyGame(const IGame2D* game)
	{
		if (game == nullptr)
			return false;

		std::free(const_cast<IGame2D*>(game));
		return true;
	}
}
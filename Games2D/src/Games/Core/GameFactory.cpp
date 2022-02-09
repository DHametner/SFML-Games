#include "gmspch.hpp"
#include "GameFactory.hpp"
#include "Games2D.hpp"

namespace gms
{
	IGame2D* GameFactory::createGame(const Type& type)
	{
		IGame2D* game = nullptr;

		switch (type)
		{
		case Type::TicTacToe:

			game = new gms::TicTacToe;
			break;
		case Type::ConnectFour:

			game = new ConnectFour;
			break;	
		case Type::Unknown:
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
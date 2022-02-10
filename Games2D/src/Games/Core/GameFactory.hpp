#pragma once

#include "Core/Game.hpp"

namespace gms
{
	class GameFactory
	{
	public:
		static IGame2D* createGame(const Type&, bool = false);

		static bool destroyGame(const IGame2D*);
	};
}
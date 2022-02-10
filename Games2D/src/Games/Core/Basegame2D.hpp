#pragma once

#include "gmspch.hpp"
#include "Config.hpp"
#include "GameTypes.hpp"
#include "GameStates.hpp"

namespace gms
{
	struct Player
	{
		int32_t		id;
		std::string name;
		sf::Texture sign;
	};

	struct Field
	{
		sf::RectangleShape cell;
		int32_t			   ownerId;
	};

	class IGame2D : public Configurable
	{
	public:
		virtual bool hasWon(int32_t) = 0;
		
		virtual int32_t getPlayerMove(int32_t) = 0;

		virtual void run() = 0;
	};

	class IBoard2D : public Configurable
	{
	public:
		virtual bool isFull() = 0;

		virtual Field& at(int32_t) = 0;

		virtual bool applyMove(int32_t, const Player&) = 0;
	};
}
#pragma once

#include "gmspch.hpp"

namespace gms
{
	constexpr int    CONNECTFOUR_COLUMNS = 7;
	constexpr int    CONNECTFOUR_ROWS    = 6;
	constexpr size_t CONNECTFOUR_SIZE    = CONNECTFOUR_COLUMNS * CONNECTFOUR_ROWS;

	constexpr int    TICTACTOE_COLUMNS   = 3;
	constexpr int    TICTACTOE_ROWS      = 3;
	constexpr size_t TICTACTOE_SIZE      = TICTACTOE_COLUMNS * TICTACTOE_ROWS;

	class Config
	{
	public:
		const float_t kCellWidth = 200.0f;
		const float_t kCellHeight = 200.0f;
		const sf::Vector2f kCellSize = sf::Vector2f(kCellWidth, kCellHeight);

		float_t border = 0.0f;
		int32_t columns = 0;
		int32_t rows = 0;

		std::string name;

	public:
		Config() = default;
		Config(const Config&) = default; 
		virtual ~Config() = default;
	};

	class Configurable
	{
	protected:
		Config config;

	public:
		void configure(const Config&);
	};
}
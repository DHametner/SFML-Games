#pragma once

#include "gmspch.hpp"
#include "Basegame2D.hpp"
#include "Core/Game.hpp"

namespace gms
{
	template<size_t Size>
	class Board : public IBoard2D
	{
	protected:
		GameContext*            context;
		std::array<Field, Size> cells;

	public:
		Board();
		Board(const Board& board) = default;
		virtual ~Board() = default;

	public:
		bool isFull() override;

		Field& at(int32_t idx);
	};

	template<size_t Size>
	inline Board<Size>::Board()
	{
		context = GameContext::getInstance();

		for (int32_t idx = 0; idx < cells.size(); idx++)
		{
			cells[idx].ownerId = 0;
		}
	}

	template<size_t Size>
	inline bool Board<Size>::isFull()
	{
		if (context->currentState() == State::Full)
			return true;

		for (int32_t idx = 0; idx < cells.size(); idx++)
		{
			if (cells[idx].ownerId == 0)
				return false;
		}
		return true;
	}
	template<size_t Size>
	inline Field& Board<Size>::at(int32_t idx)
	{
		return cells[idx];
	}
}
#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"

namespace SnakeGame
{
	enum CellState
	{
		Empty,
		SnakeItem,
		AppleItem,
		WallItem
	};

	struct Cell
	{		
		CellState state = CellState::Empty;
		sf::RectangleShape SetShape(int x,int y)
		{
			sf::RectangleShape shape;
			shape.setSize({ CELL_SIZE, CELL_SIZE });
			shape.setFillColor(sf::Color::Red);
			shape.setPosition(CELL_SIZE*x,CELL_SIZE*y);
			return shape;
		}

		void SetCellState(CellState& currentState)
		{
			state = currentState;
		}
		CellState GetCellState()
		{
			return state;
		}
	};
	struct GameBoard
	{
		sf::RectangleShape SetShapeParametr( sf::Vector2f size, sf::Color color,  sf::Vector2f position)
		{
			sf::RectangleShape shape;
			shape.setSize(size);
			shape.setFillColor(color);
			shape.setPosition(position);
			return shape;
		}
		Cell cell;
		std::vector<std::vector<Cell>> cells;
	};


	void InitGameBoard(GameBoard& board);
	void UpdateGameBoard(GameBoard& board);
	void DrawGameBoard(GameBoard& board, sf::RenderWindow& window);
}
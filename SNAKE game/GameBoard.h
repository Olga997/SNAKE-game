#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"

namespace SnakeGame
{
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
	};
	enum CellState
	{
		Empty,
		Snake,
		Apple,
		Walls
	};

	struct Cell
	{
		sf::RectangleShape cell;
		CellState state = CellState::Apple;
	};

	void InitGameBoard(GameBoard& board);
	void UpdateGameBoard(GameBoard& board);
	void DrawGameBoard(GameBoard& board, sf::RenderWindow& window);
}
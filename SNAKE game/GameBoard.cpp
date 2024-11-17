#include "GameBoard.h"

namespace SnakeGame 
{
	void InitGameBoard(GameBoard& board)
	{
		std::vector<Cell> cells[NUMBER_CELL][NUMBER_CELL];

		
	}

	
	void UpdateGameBoard(GameBoard& board)
	{
		
	}
	void DrawGameBoard(GameBoard& board, sf::RenderWindow& window)
	{
		window.draw(board.SetShapeParametr({ SCREEN_WIDTH, SCREEN_HIGHT }, sf::Color(116, 194, 79), { 0.f,0.f }));
		window.draw(board.SetShapeParametr({ SCREEN_WIDTH, 40.f }, sf::Color(63, 115, 39), { 0.f,0.f }));
		window.draw(board.SetShapeParametr({ SCREEN_WIDTH-40.f, SCREEN_HIGHT-80.f }, sf::Color(172, 250, 112), { 20.f,60.f }));
	}
}
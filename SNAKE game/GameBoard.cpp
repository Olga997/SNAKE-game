#include "GameBoard.h"

namespace SnakeGame 
{
	void InitGameBoard(GameBoard& board)
	{
		board.cells.reserve(NUMBER_CELL * NUMBER_CELL);

		for (int i = 0; i < NUMBER_CELL; i++)
		{
			std::vector<Cell> temp;
			for (int j = 0; j < NUMBER_CELL; j++)
			{
				temp.push_back(board.cell);
				board.cell.SetShape(i, j);
			}
		}
		
	}
	
	
	void UpdateGameBoard(GameBoard& board)
	{
		
	}
	void DrawGameBoard(GameBoard& board, sf::RenderWindow& window)
	{
		window.draw(board.SetShapeParametr({ SCREEN_WIDTH, SCREEN_HIGHT }, sf::Color(116, 194, 79), { 0.f,0.f }));
		window.draw(board.SetShapeParametr({ SCREEN_WIDTH, 40.f }, sf::Color(63, 115, 39), { 0.f,0.f }));
		window.draw(board.SetShapeParametr({ SCREEN_WIDTH-40.f, SCREEN_HIGHT-80.f }, sf::Color(172, 250, 112), { 20.f,60.f }));
		for (int i = 0; i < NUMBER_CELL; i++)
		{
	
			for (int j = 0; j < NUMBER_CELL; j++)
			{
				window.draw(board.cells.)
			}
		}
		
	}
}
#include "Game.h"

namespace SnakeGame
{
	void InitGame(Game& game)
	{
		InitGameBoard(game.board);
		InitSnake(game.snake);
	}
	void HandeleWindowEvents(Game& game, sf::RenderWindow& window)
	{
		//Read event
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window if close button or Escape key pressed
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
		}
	}

	bool UpdateGame(Game& game, float deltaTime)
	{
		UpdateSnake(game.snake, deltaTime);
		return true;
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		DrawGameBoard(game.board, window);
		DrawSnake(game.snake, window);
	}
	void ShutDownGame(Game& game)
	{
	}
}

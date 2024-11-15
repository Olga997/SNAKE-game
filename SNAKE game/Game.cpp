#include "Game.h"
#include "GameBoard.h"

namespace SnakeGame
{
	void InitGame(Game& game)
	{
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

	bool UpdateGame(Game& game)
	{
		return true;
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{

	}
	void ShutDownGame(Game& game)
	{
	}
}

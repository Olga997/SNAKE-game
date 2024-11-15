#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Settings.h"
#include "Game.h"

using namespace SnakeGame;

int main()
{
	sf::RenderWindow window(sf::VideoMode(SnakeGame::SCREEN_WIDTH, SnakeGame::SCREEN_HIGHT), "SnakeGame");
	SnakeGame::Game* game = new SnakeGame::Game();
	InitGame(*game);

	//Main loop
	while (window.isOpen())
	{
		HandeleWindowEvents(*game,window);
		if (!window.isOpen())
		{
			break;
		}
		//UpdateGame
		if (UpdateGame(*game))
		{
			window.clear();

			DrawGame(*game, window);

			window.display();
		}
		else
		{
			window.close();
		}
	}
	ShutDownGame(*game);
	delete game;
	game = nullptr;
	return 0;
}

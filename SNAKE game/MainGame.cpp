#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Settings.h"
#include "Game.h"

using namespace SnakeGame;

int main()
{
	int seed = (int)time(nullptr);
	srand(seed);

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HIGHT), "SnakeGame");
	SnakeGame::Game* game = new SnakeGame::Game();
	InitGame(*game);

	//Timer
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	//Main loop
	while (window.isOpen())
	{
		HandleWindowEvents(*game, window);
		if (!window.isOpen())
		{
			break;
		}
		//Calculate time delta
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		//UpdateGame
		if (UpdateGame(*game, deltaTime))
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
	ShutdownGame(*game);
	delete game;
	game = nullptr;
	return 0;
}

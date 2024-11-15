#pragma once
#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace SnakeGame
{
	struct Game
	{

	};

	void InitGame(Game& game);
	void HandeleWindowEvents(Game& game, sf::RenderWindow& window);
	bool UpdateGame(Game& game);
	void DrawGame(Game& game, sf::RenderWindow&window);
	void ShutDownGame(Game& game);
}
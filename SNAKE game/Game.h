#pragma once
#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameBoard.h"
#include "Apple.h"
#include "Snake.h"

namespace SnakeGame
{
	struct Game
	{
		GameBoard board;
		Snake snake;
	};

	void InitGame(Game& game);
	void HandeleWindowEvents(Game& game, sf::RenderWindow& window);
	bool UpdateGame(Game& game, float deltaTime);
	void DrawGame(Game& game, sf::RenderWindow&window);
	void ShutDownGame(Game& game);
}
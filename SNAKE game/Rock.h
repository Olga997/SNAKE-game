#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace SnakeGame
{
	struct Rock
	{
		sf::Texture& texture;
		Position2D position;
		sf::Sprite sprite;
	};

	void InitRock(Rock& rock);
	void DrawRock(Rock& rock, sf::RenderWindow& window);
}

#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "Math.h"


namespace SnakeGame
{
	struct Apple
	{
		sf::Texture texture;
		Position2D position;
		sf::Sprite sprite;
		bool IsAppleEaten = false;
	};

	void InitApple(Apple& apple);

	void DrawApple(Apple& apple, sf::RenderWindow& window);
}

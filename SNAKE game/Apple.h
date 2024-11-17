#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"


namespace SnakeGame
{
	struct Apple
	{
		sf::Vector2f position;
		sf::Sprite sprite;
		sf::Texture texture;
	};
	void InitApple(Apple& apple);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
}

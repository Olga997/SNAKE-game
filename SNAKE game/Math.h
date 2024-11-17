#pragma once
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	void SetSpriteSize(sf::Sprite& sprite, sf::Vector2f desiredSize);
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, sf::Vector2f origin);
}

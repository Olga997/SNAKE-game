#include "Math.h"
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	void SetSpriteSize(sf::Sprite& sprite, sf::Vector2f desiredSize)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredSize.x / spriteRect.width, desiredSize.y / spriteRect.height };
		sprite.setScale(scale);
	}
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, sf::Vector2f origin)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(origin.x * spriteRect.width, origin.y * spriteRect.height);
	}
}

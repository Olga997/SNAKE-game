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
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
	}
}

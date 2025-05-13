#include "Apple.h"
#include"Settings.h"
#include"Math.h"
#include <cassert>

namespace SnakeGame
{
	void InitApple(Apple& apple)
	{
		assert(apple.texture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));

		//Init apples sprite
		apple.sprite.setTexture(apple.texture);
		SetSpriteSize(apple.sprite, APPLE_SIZE, APPLE_SIZE);
		SetSpriteRelativeOrigin(apple.sprite, 0.5f, 0.5f);
	}
		
	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		window.draw(apple.sprite);
	}
}
#pragma once
#include <SFML/Graphics.hpp>
#include <list>

namespace SnakeGame
{
	struct Vector2D
	{
		float x = 0;
		float y = 0;
	};
	Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs);

	typedef Vector2D Position2D;

	sf::Vector2f GetRandomSpritePositionInRectangle(const sf::Sprite& sprite, const sf::FloatRect& rect);
	

	bool IsBorderCollide(Position2D playerPosition, float screenWidth, float screenHight);
	bool IsRocksCollide(Position2D rect1Position, Vector2D rect1Size,
		Position2D rect2Position, Vector2D rect2Size);
	bool IsAppleCollide(Position2D circle1Position, Vector2D circle1Size,
		Position2D circle2Position, Vector2D circle2Size);
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desireHight);
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);
	sf::Vector2f GetTextOrigin(const sf::Text& text, const Vector2D& relativePosition);
	int GetRandomNumber(int MinNumber, int MaxNumber);

	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);
}

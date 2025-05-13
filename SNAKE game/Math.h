#pragma once
#include <SFML/Graphics.hpp>
#include <list>

namespace SnakeGame
{
	//Text
	enum class Orientation
	{
		Horizontal,
		Vertical
	};
	enum class Alignment
	{
		Min,
		Middle,
		Max
	};

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
	void SetSpriteRandomPosition(sf::Sprite& sprite, const sf::FloatRect& rect, const std::list<sf::Sprite>& collection);
	int GetRandomNumber(int MinNumber, int MaxNumber);

	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);

	template<class InputIt>
	void DrawSprites(InputIt first, const InputIt last, sf::RenderWindow& window) {
		for (; first != last; ++first) {
			window.draw(*first);
		}
	}

	float GetManhattanDistanceBetweenSprites(const sf::Sprite& spriteFrom, const sf::Sprite& spriteTo);
	sf::Vector2f GetVectorBetweenSprites(const sf::Sprite& spriteFrom, const sf::Sprite& spriteTo);
	bool CheckSpriteIntersection(const sf::Sprite& sprite1, const sf::Sprite& sprite2);

	template<class InputIt>
	bool FullCheckCollisions(InputIt first, const InputIt last, const sf::Sprite& sprite) {
		for (; first != last; ++first) {
			if (CheckSpriteIntersection(*first, sprite)) {
				return true;
			}
		}
		return false;
	}

	sf::Vector2f GetTextOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);
	void DrawTextList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin);
}

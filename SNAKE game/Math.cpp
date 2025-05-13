#include "Math.h"
#include "Settings.h"
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs)
	{
		Vector2D result;
		result.x = lhs.x + rhs.x;
		result.y = lhs.y + rhs.y;
		return result;
	}
	sf::Vector2f GetRandomSpritePositionInRectangle(const sf::Sprite& sprite, const sf::FloatRect& rect)
	{
		sf::Vector2f result;
		const auto spriteWidth = sprite.getGlobalBounds().width;
		const auto spriteHeight = sprite.getGlobalBounds().height;
		result.x = rand() / (float)RAND_MAX * (rect.width - 2 * spriteWidth) + rect.left + spriteWidth;
		result.y = rand() / (float)RAND_MAX * (rect.height - 2 * spriteHeight) + rect.top + spriteHeight;
		return result;
	}


	bool IsBorderCollide(Position2D playerPosition, float screenWidth, float screenHight)
	{
		return(playerPosition.x - SNAKE_SIZE / 2.f < 0.f || playerPosition.x + SNAKE_SIZE / 2.f > screenWidth ||
			playerPosition.y - SNAKE_SIZE / 2.f < 0.f || playerPosition.y + SNAKE_SIZE / 2.f > screenHight);
	}
	bool IsRocksCollide(Position2D rect1Position, Vector2D rect1Size, Position2D rect2Position, Vector2D rect2Size)
	{
		float dx = (float)fabs(rect1Position.x - rect2Position.x);
		float dy = (float)fabs(rect1Position.y - rect2Position.y);
		return (dx <= (rect1Size.x + rect2Size.x) / 2.f &&
			dy <= (rect1Size.y + rect2Size.y) / 2.f);
	}
	bool IsAppleCollide(Position2D circle1Position, Vector2D circle1Size, Position2D circle2Position, Vector2D circle2Size)
	{
		float squareDistance = (circle1Position.x - circle2Position.x) * (circle1Position.x - circle2Position.x)
			+ (circle1Position.y - circle2Position.y) * (circle1Position.y - circle2Position.y);
		float squareRadiusSum = (circle1Size.x + circle2Size.x) * (circle1Size.y + circle2Size.y) / 4.f;
		return (squareDistance <= squareRadiusSum);
	}
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desireHight)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desireHight / spriteRect.height };
		sprite.setScale(scale);
	}
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
	}
	void SetSpriteRandomPosition(sf::Sprite& sprite, const sf::FloatRect& rect, const std::list<sf::Sprite>& collection)
	{
		do {
			const auto newPosition = GetRandomSpritePositionInRectangle(sprite, rect);
			sprite.setPosition(newPosition);
		} while (FullCheckCollisions(collection.begin(), collection.end(), sprite));
	}
	
	int GetRandomNumber(int MinNumber, int MaxNumber)
	{
		int result;
		result = MinNumber + rand() % (MaxNumber + 1 - MinNumber);
		return result;
	}
	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition)
	{
		sf::FloatRect textSize = text.getLocalBounds();
		return {
			(textSize.left + textSize.width) * relativePosition.x,
			(textSize.top + textSize.height) * relativePosition.y,
		};
	}

	float GetManhattanDistanceBetweenSprites(const sf::Sprite& spriteFrom, const sf::Sprite& spriteTo)
	{
		const auto result = spriteTo.getPosition() - spriteFrom.getPosition();
		return std::fabs(result.x) + std::fabs(result.y);
	}

	sf::Vector2f GetVectorBetweenSprites(const sf::Sprite& spriteFrom, const sf::Sprite& spriteTo)
	{
		const auto result = spriteTo.getPosition() - spriteFrom.getPosition();
		return result;
	}

	bool CheckSpriteIntersection(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
		const auto distance = sprite1.getPosition() - sprite2.getPosition();
		if (sqrtf(distance.x * distance.x + distance.y * distance.y) * 2 < sprite1.getGlobalBounds().width + sprite2.getGlobalBounds().width) {
			return true;
		}
		return false;
	}

	sf::Vector2f GetTextOrigin(const sf::Text& text, const sf::Vector2f& relativePosition)
	{
		sf::FloatRect textSize = text.getLocalBounds();
		return {
			(textSize.left + textSize.width) * relativePosition.x,
			(textSize.top + textSize.height) * relativePosition.y,
		};
	}
	void DrawTextList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin)
	{
		sf::FloatRect totalRect;
		// Calculate total height/width of all texts
		for (auto it = items.begin(); it != items.end(); ++it)
		{
			sf::FloatRect itemRect = (*it)->getGlobalBounds();

			if (orientation == Orientation::Horizontal)
			{
				totalRect.width += itemRect.width + (it != items.end() - 1 ? spacing : 0.f);
				totalRect.height = std::max(totalRect.height, itemRect.height);
			}
			else
			{
				totalRect.width = std::max(totalRect.width, itemRect.width);
				totalRect.height += itemRect.height + (it != items.end() - 1 ? spacing : 0.f);
			}
		}

		totalRect.left = position.x - origin.x * totalRect.width;
		totalRect.top = position.y - origin.y * totalRect.height;
		sf::Vector2f currentPos = { totalRect.left, totalRect.top };

		for (auto it = items.begin(); it != items.end(); ++it)
		{
			sf::FloatRect itemRect = (*it)->getGlobalBounds();
			sf::Vector2f itemOrigin;

			if (orientation == Orientation::Horizontal)
			{
				itemOrigin.y = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
				itemOrigin.x = 0.f;
				currentPos.y = totalRect.top + itemOrigin.y * totalRect.height;
			}
			else
			{
				itemOrigin.y = 0.f;
				itemOrigin.x = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
				currentPos.x = totalRect.left + itemOrigin.x * totalRect.width;
			}

			(*it)->setOrigin(GetTextOrigin(**it, itemOrigin));
			(*it)->setPosition(currentPos);
			window.draw(**it);

			if (orientation == Orientation::Horizontal)
			{
				currentPos.x += itemRect.width + spacing;
			}
			else
			{
				currentPos.y += itemRect.height + spacing;
			}


		}
	}
}

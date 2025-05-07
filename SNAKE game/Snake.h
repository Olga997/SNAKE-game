#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"
#include <list>
#include <array>

namespace SnakeGame
{
	enum class SnakeDirection
	{
		Up = 0,
		Right,
		Down,
		Left
	};

	enum class SnakePart : uint8_t
	{
		Head = 0,
		Body,
		BodyBend,
		Tail,
		Count
	};

	struct Snake
	{
		std::list<sf::Sprite> body;
		std::list<sf::Sprite>::iterator head;
		std::list<sf::Sprite>::iterator tail;
		float speed = 0.f;
		SnakeDirection direction = SnakeDirection::Up;
		SnakeDirection prevDirection = SnakeDirection::Up;

		sf::Texture textureHead;
		sf::Texture textureBody;
		sf::Texture textureBodyBend;
		sf::Texture textureTail;

	};

	void LoadSnakeTextures(Snake& snake);
	float GetManhattanDistanceBetweenSprites(const sf::Sprite& spriteFrom, const sf::Sprite& spriteTo);
	sf::Vector2f GetVectorBetweenSprites(const sf::Sprite& spriteFrom, const sf::Sprite& spriteTo);
	
	void InitSnake(Snake& snake);
	void MoveSnake(Snake& snake, float timeDelta);
	void GrowSnake(Snake& snake);
	void DrawSnake(Snake& snake, sf::RenderWindow& window);

	bool HasSnakeCollisionWithRect(const Snake& snake, const sf::FloatRect& rect);
	bool CheckSnakeCollisionWithHimself(Snake& snake);
	bool CheckSnakeCollisionWithSprite(Snake& snake, const sf::Sprite& sprite);

	sf::Vector2f GetDirectionVector(SnakeDirection direction);
}

#pragma once
#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Settings.h"
#include "Math.h"

namespace SnakeGame
{
	enum class SnakeDirection
	{
		Right = 0,
		UP,
		Left,
		Down
	};

	struct Snake
	{
		sf::Vector2f position;
		float speed = INITIAL_SPEED;
		SnakeDirection direction = SnakeDirection::Right;
		sf::Sprite sprite;
		sf::Texture texture;
	};

	void InitSnake(Snake& snake);
	void UpdateSnake(Snake& snake, float deltaTime);
	void DrawSnake(Snake& snake, sf::RenderWindow& window);
}


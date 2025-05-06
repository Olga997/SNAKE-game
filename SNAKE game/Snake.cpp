#include "Snake.h"
#include <cassert>

namespace SnakeGame
{
	void InitSnake(Snake& snake)
	{
		assert(snake.texture.loadFromFile(RESOURCES_PATH + "\\Snake_head.png"));

		snake.position = { SCREEN_WIDTH / 2.f,SCREEN_HIGHT / 2.f };
		snake.speed = INITIAL_SPEED;
		snake.direction = SnakeDirection::Right;

		//Init snake sprite
		snake.sprite.setTexture(snake.texture);
		SetSpriteSize(snake.sprite,  SNAKE_SIZE, SNAKE_SIZE );
		SetSpriteRelativeOrigin(snake.sprite,  0.5f, 0.5f );
	}
	void UpdateSnake(Snake& snake, float deltaTime)
	{
		//Update player position
		/*switch (snake.direction)
		{
		case SnakeDirection::Right:
		{
			snake.position.x += snake.speed * deltaTime;
			SetSpriteSize(snake.sprite, { SNAKE_SIZE, SNAKE_SIZE });
			snake.sprite.setRotation(0.f);
			break;
		}
		case SnakeDirection::UP:
		{
			snake.position.y -= snake.speed * deltaTime;
			SetSpriteSize(snake.sprite, { SNAKE_SIZE, SNAKE_SIZE });
			snake.sprite.setRotation(-90.f);
			break;
		}
		case SnakeDirection::Left:
		{
			snake.position.x -= snake.speed * deltaTime;
			SetSpriteSize(snake.sprite, {- SNAKE_SIZE, SNAKE_SIZE });
			snake.sprite.setRotation(0.f);
			break;
		}
		case SnakeDirection::Down:
		{
			snake.position.y += snake.speed * deltaTime;
			SetSpriteSize(snake.sprite, { SNAKE_SIZE, SNAKE_SIZE });
			snake.sprite.setRotation(90.f);
			break;
		}
		}*/
	}
	void DrawSnake(Snake& snake, sf::RenderWindow& window)
	{
		snake.sprite.setPosition(snake.position.x, snake.position.y);
		window.draw(snake.sprite);
	}
}

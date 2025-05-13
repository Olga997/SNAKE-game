#include "Snake.h"
#include "Math.h"
#include "Settings.h"
#include <assert.h>

namespace SnakeGame
{
	void LoadSnakeTextures(Snake& snake)
	{
		assert(snake.textureHead.loadFromFile(RESOURCES_PATH + "Head.png"));
		assert(snake.textureBody.loadFromFile(RESOURCES_PATH + "Body.png"));
		assert(snake.textureBodyBend.loadFromFile(RESOURCES_PATH + "BodyBend.png"));
		assert(snake.textureTail.loadFromFile(RESOURCES_PATH + "Tail.png"));
	}

	void SetHeadSprite(SnakeGame::Snake& snake, std::list<sf::Sprite>::iterator it)
	{
		float angle = 0.f;
		if (snake.direction == SnakeGame::SnakeDirection::Right)
		{
			angle = 90.f;
		}
		else if (snake.direction == SnakeGame::SnakeDirection::Down)
		{
			angle = 180.f;
		}
		else if (snake.direction == SnakeGame::SnakeDirection::Left)
		{
			angle = -90.f;
		}

		it->setTexture(snake.textureHead);
		it->setRotation(angle);
	}
	void SetTailSprite(SnakeGame::Snake& snake, std::list<sf::Sprite>::iterator it)
	{
		it->setTexture(snake.textureTail);

		auto nextIt = std::next(it);
		if (nextIt == snake.body.end()) {
			return;
		}

		float angle = 0.f;
		if (nextIt->getPosition().x < it->getPosition().x)
		{
			angle = -90.f;
		}
		else if (nextIt->getPosition().x > it->getPosition().x)
		{
			angle = 90.f;
		}
		else if (nextIt->getPosition().y > it->getPosition().y)
		{
			angle = 180.f;
		}

		it->setRotation(angle);
	}

	sf::Sprite GetRotationSprite(Snake& snake, SnakeDirection oldDirection, SnakeDirection newDirection)
	{
		sf::Sprite spriteHeadBend;
		spriteHeadBend.setTexture(snake.textureBodyBend);
		SetSpriteSize(spriteHeadBend, SNAKE_SIZE, SNAKE_SIZE);
		SetSpriteRelativeOrigin(spriteHeadBend, 0.5f, 0.5f);

		float angle = 0.f;
		if (oldDirection == SnakeGame::SnakeDirection::Right && newDirection == SnakeGame::SnakeDirection::Up ||
			oldDirection == SnakeGame::SnakeDirection::Down && newDirection == SnakeGame::SnakeDirection::Left) 
		{
			angle = 0.f;
		}
		else if (oldDirection == SnakeGame::SnakeDirection::Down && newDirection == SnakeGame::SnakeDirection::Right ||
			oldDirection == SnakeGame::SnakeDirection::Left && newDirection == SnakeGame::SnakeDirection::Up) 
		{
			angle = 90.f;
		}
		else if (oldDirection == SnakeGame::SnakeDirection::Left && newDirection == SnakeGame::SnakeDirection::Down ||
			oldDirection == SnakeGame::SnakeDirection::Up && newDirection == SnakeGame::SnakeDirection::Right) 
		{
			angle = 180;
		}
		else if (oldDirection == SnakeGame::SnakeDirection::Up && newDirection == SnakeGame::SnakeDirection::Left ||
			oldDirection == SnakeGame::SnakeDirection::Right && newDirection == SnakeGame::SnakeDirection::Down) 
		{
			angle = -90.f;
		}

		spriteHeadBend.setRotation(angle);
		return spriteHeadBend;
	}	

	void InitSnake(Snake& snake, Game& game)
	{
		sf::Sprite spriteHead;
		spriteHead.setTexture(snake.textureHead);
		SetSpriteSize(spriteHead, SNAKE_SIZE, SNAKE_SIZE);
		SetSpriteRelativeOrigin(spriteHead, 0.5f, 0.5f);
		spriteHead.setPosition((float)SCREEN_WIDTH / 2.f, (float)SCREEN_HEGHT / 2.f);
		snake.body.push_front(spriteHead);

		sf::Sprite spriteTail;
		spriteTail.setTexture(snake.textureTail);
		SetSpriteSize(spriteTail, SNAKE_SIZE, SNAKE_SIZE);
		SetSpriteRelativeOrigin(spriteTail, 0.5f, 0.5f);
		spriteTail.setPosition((float)SCREEN_WIDTH / 2.f, (float)SCREEN_HEGHT / 2.f + SNAKE_SIZE * (INITIAL_SNAKE_SIZE - 1));
		snake.body.push_front(spriteTail);

		snake.head = --snake.body.end();
		snake.tail = snake.body.begin();
		snake.prevDirection = snake.direction = SnakeDirection::Up;

		float speed = 0.f;
		switch (game.gameDifficulty)
		{
		case GameDifficulty::Easy:
		{
			speed = INITIAL_SPEED;
			break;
		}
		case GameDifficulty::Normal:
		{
			speed = INITIAL_SPEED * 2.f;
			break;
		}
		case GameDifficulty::Hard:
		{
			speed = INITIAL_SPEED * 3.f;
			break;
		}
		case GameDifficulty::VeryHard:
		{
			speed = INITIAL_SPEED * 4.f;
			break;
		}
		case GameDifficulty::Nightmare:
		{
			speed = INITIAL_SPEED * 5.f;
			break;
		}
		default:
			assert(false);
			break;
		}
		snake.speed = speed;
	}

	void MoveSnake(Snake& snake, float timeDelta)
	{
		float shift = snake.speed * timeDelta;
		const sf::Vector2f direction = GetDirectionVector(snake.direction) * shift / SNAKE_SIZE;
		auto prevHead = snake.head;

		// new rotation
		if (snake.prevDirection != snake.direction)
		{
			snake.head = snake.body.insert(++snake.head, *prevHead);
			SetHeadSprite(snake, snake.head);

			*prevHead = GetRotationSprite(snake, snake.prevDirection, snake.direction);
			prevHead->setPosition(snake.head->getPosition());
		}
		snake.head->setPosition(snake.head->getPosition() + direction);

		auto nextTail = std::next(snake.tail);
		auto tailDirection = GetVectorBetweenSprites(*snake.tail, *nextTail);
		auto dist = GetManhattanDistanceBetweenSprites(*snake.tail, *nextTail);

		if (shift > dist) {
			shift -= dist;
			snake.tail = snake.body.erase(snake.tail);
			SetTailSprite(snake, snake.tail);
		}
		else {
			snake.tail->setPosition(snake.tail->getPosition() + tailDirection * shift / dist);
		}

		snake.prevDirection = snake.direction;
	}

	void GrowSnake(Snake& snake)
	{
		snake.head->setPosition(snake.head->getPosition() + GetDirectionVector(snake.direction));
	}

	void DrawSnake(Snake& snake, sf::RenderWindow& window)
	{
		for (auto it = snake.body.begin(); it != snake.head; ++it)
		{
			auto nextIt = std::next(it);
			float width = SNAKE_SIZE, height = GetManhattanDistanceBetweenSprites(*it, *nextIt) - SNAKE_SIZE;
			float angle = it->getPosition().x != nextIt->getPosition().x ? 90.f : 0.f;

			if (width > 0.f && height > 0.f) 
			{
				sf::Sprite spriteBody;
				spriteBody.setTexture(snake.textureBody);
				SetSpriteSize(spriteBody, width, height);
				SetSpriteRelativeOrigin(spriteBody, 0.5f, 0.5f);

				auto position = (it->getPosition() + nextIt->getPosition()) / 2.f;
				spriteBody.setPosition(position);
				spriteBody.setRotation(angle);
				window.draw(spriteBody);
			}
		}

		DrawSprites(snake.body.begin(), snake.body.end(), window);
	}

	bool HasSnakeCollisionWithRect(const Snake& snake, const sf::FloatRect& rect)
	{
		sf::Vector2f forwardPoint = snake.head->getPosition();
		if (snake.direction == SnakeDirection::Up)
		{
			forwardPoint.y -= SNAKE_SIZE / 2.f;
		}
		else if (snake.direction == SnakeDirection::Right)
		{
			forwardPoint.x += SNAKE_SIZE / 2.f;
		}
		else if (snake.direction == SnakeDirection::Down)
		{
			forwardPoint.y += SNAKE_SIZE / 2.f;
		}
		else 
		{
			forwardPoint.x -= SNAKE_SIZE / 2.f;
		}

		bool result = rect.contains(forwardPoint);
		return result;
	}

	bool CheckSnakeCollisionWithHimself(Snake& snake)
	{
		auto curIt = snake.tail;
		auto nextIt = std::next(snake.tail);
		while (nextIt != snake.head) {
			auto curRect = curIt->getGlobalBounds();
			auto nextRect = nextIt->getGlobalBounds();

			sf::FloatRect unionRect;
			unionRect.top = std::min(curRect.top, nextRect.top);
			unionRect.left = std::min(curRect.left, nextRect.left);
			unionRect.width = std::fabs(curRect.left - nextRect.left) + SNAKE_SIZE;
			unionRect.height = std::fabs(curRect.top - nextRect.top) + SNAKE_SIZE;

			if (HasSnakeCollisionWithRect(snake, unionRect)) {
				return true;
			}
			curIt = nextIt;
			nextIt = std::next(nextIt);
		}
		return false;
	}

	bool CheckSnakeCollisionWithSprite(Snake& snake, const sf::Sprite& sprite)
	{
		auto curIt = snake.tail;

		while (curIt != snake.head) {
			auto nextIt = std::next(curIt);
			auto curRect = curIt->getGlobalBounds();
			auto nextRect = nextIt->getGlobalBounds();

			sf::FloatRect unionRect;
			unionRect.top = std::min(curRect.top, nextRect.top);
			unionRect.left = std::min(curRect.left, nextRect.left);
			unionRect.width = std::fabs(curRect.left - nextRect.left) + SNAKE_SIZE;
			unionRect.height = std::fabs(curRect.top - nextRect.top) + SNAKE_SIZE;

			if (HasSnakeCollisionWithRect(snake, unionRect)) {
				return true;
			}
			curIt = nextIt;
		}
		return false;
	}

	sf::Vector2f GetDirectionVector(SnakeDirection direction)
	{
		sf::Vector2f result;

		switch (direction)
		{
		case SnakeDirection::Up:
		{
			result = { 0.f, -SNAKE_SIZE };
			break;
		}
		case SnakeDirection::Right:
		{
			result = { SNAKE_SIZE, 0.f };
			break;
		}
		case SnakeDirection::Down:
		{
			result = { 0.f, SNAKE_SIZE };
			break;
		}
		case SnakeDirection::Left:
		{
			result = { -SNAKE_SIZE, 0.f };
			break;
		}

		return result;
		}
	}
}

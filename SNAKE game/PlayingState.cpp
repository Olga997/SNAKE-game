#include "PlayingState.h"

namespace SnakeGame
{
	void InitPlayingState(PlayingStateData& data, Game& game)
	{
		InitSnake(data.snake);
		InitGameBoard(data.board);

	}
	void HandlePlayingStateWindowEvent(PlayingStateData& data, Game& game, const sf::Event& event)
	{

	}
	void SnakeGame::HandeInput(PlayingStateData& data)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			data.snake.direction = SnakeDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			data.snake.direction = SnakeDirection::UP;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			data.snake.direction = SnakeDirection::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			data.snake.direction = SnakeDirection::Down;
		}
	}
	void UpdatePlayingStateData(PlayingStateData& data, Game& game, float deltaTime)
	{
		HandeInput(data);
		UpdateSnake(data.snake, deltaTime);
	}
	void DrawPlayingState(PlayingStateData& data, Game& game, sf::RenderWindow& window)
	{
		DrawGameBoard(data.board, window);
		DrawSnake(data.snake, window);
	}
	void ShutdownPlayingState(PlayingStateData& data, Game& game)
	{
	}
}

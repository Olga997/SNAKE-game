#include "PlayingState.h"
#include "Game.h"
#include <assert.h>



namespace SnakeGame
{
	void InitPlayingState(PlayingStateData& data, Game& game)
	{
		InitSnake(data.snake);

		InitGameBoard(data.board);

		assert(data.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
		assert(data.rockTexture.loadFromFile(RESOURCES_PATH + "Rock.png"));
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));
		assert(data.eatAppleSoundBuffer.loadFromFile(RESOURCES_PATH + "AppleEat.wav"));
		assert(data.gameOverSoundBuffer.loadFromFile(RESOURCES_PATH + "Death.wav"));

		InitApple(data.apple);
				
		//Init rock
		/*data.rocks.resize(NUM_ROCK);
		for (Rock& rock:data.rocks)
		{
			InitRock(rock);
		}*/

		game.numEatenApples = 0;

		data.scoreText.setFont(data.font);
		data.scoreText.setCharacterSize(24);
		data.scoreText.setFillColor(sf::Color::White);
	}


	void HandlePlayingStateWindowEvent(PlayingStateData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PushGameState(game, GameStateType::Pause, false);
			}
		}
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
	void UpdatePlayingState(PlayingStateData& data, Game& game, float deltaTime)
	{
		HandeInput(data);
		UpdateSnake(data.snake, deltaTime);
		/*if (CheckSpriteIntersection(*data.snake.head, data.apple)) {
			data.eatAppleSound.play();

			GrowSnake(data.snake);

			// Increase eaten apples counter
			data.numEatenApples++;

			// Move apple to a new random position
			SetSpriteRandomPosition(data.apple, data.background.getGlobalBounds(), data.snake.body);

			// Increase snake speed
			if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::WithAcceleration) {
				data.snake.speed += ACCELERATION;
			}
		}
		bool isGameFinished = !((std::uint8_t)game.options & (std::uint8_t)GameOptions::InfiniteApples);

		if (isGameFinished
			|| !HasSnakeCollisionWithRect(data.snake, data.background.getGlobalBounds()) // Check collision with screen border
			|| CheckSnakeCollisionWithHimself(data.snake)		// Check collision with screen border
			|| FullCheckCollisions(data.rocks.begin(), data.rocks.end(), *data.snake.head)) // Check collision with rocks
		{
			data.gameOverSound.play();

			// Find snake in records table and update his score
			game.recordsTable[PLAYER_NAME] = std::max(game.recordsTable[PLAYER_NAME], data.numEatenApples);

			PushGameState(game, GameStateType::GameOver, false);
		}

		data.scoreText.setString("Apples eaten: " + std::to_string(data.numEatenApples));*/
	}

	

	void DrawPlayingState(PlayingStateData& data, Game& game, sf::RenderWindow& window)
	{
		DrawGameBoard(data.board, window);
		DrawSnake(data.snake, window);
		DrawApple(data.apple, window);
		//DrawRock(data.rocks.begin(), data.rocks.end(), window);
	}
	void ShutdownPlayingState(PlayingStateData& data, Game& game)
	{
	}
}

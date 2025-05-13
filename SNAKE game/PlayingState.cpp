#include "PlayingState.h"
#include "Game.h"
#include <string>
#include <assert.h>



namespace SnakeGame
{
	void InitPlayingState(PlayingStateData& data, Game& game)
	{
		LoadSnakeTextures(data.snake);
		assert(data.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
		assert(data.rockTexture.loadFromFile(RESOURCES_PATH + "Rock.png"));
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));
		assert(data.eatAppleSoundBuffer.loadFromFile(RESOURCES_PATH + "AppleEat.wav"));
		assert(data.gameOverSoundBuffer.loadFromFile(RESOURCES_PATH + "Death.wav"));

		data.header.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEGHT));
		data.header.setPosition(0.f, 0.f);
		data.header.setFillColor(sf::Color(116, 194, 79));

		data.outBoard.setSize(sf::Vector2f(SCREEN_WIDTH, 40.f ));
		data.outBoard.setPosition(0.f, 0.f);
		data.outBoard.setFillColor(sf::Color(63, 115, 39));

		data.inerBoard.setSize(sf::Vector2f(SCREEN_WIDTH - 40.f, SCREEN_HEGHT - 80.f));
		data.inerBoard.setPosition(20.f, 60.f);
		data.inerBoard.setFillColor(sf::Color(172, 250, 112));

		/*InitGameBoard(data.header, {SCREEN_WIDTH,SCREEN_HEGHT}, sf::Color(116, 194, 79), {0.f,0.f});
		InitGameBoard(data.outBoard, {SCREEN_WIDTH, 40.f}, sf::Color(63, 115, 39), {0.f,0.f});
		InitGameBoard(data.inerBoard, { SCREEN_WIDTH - 40.f, SCREEN_HEGHT - 80.f }, sf::Color(172, 250, 112), { 20.f,60.f });*/

		InitSnake(data.snake,game);

		InitApple(data.apple);
		SetSpriteRandomPosition(data.apple.sprite, data.inerBoard.getGlobalBounds(), data.snake.body);
				

		int numEatenApples = 0;
		int score = 0;

		data.appleText.setFont(data.font);
		data.appleText.setCharacterSize(24);
		data.appleText.setFillColor(sf::Color::White);
		
		data.scoreText.setFont(data.font);
		data.scoreText.setCharacterSize(24);
		data.scoreText.setFillColor(sf::Color::Yellow);

		data.inputHintText.setFont(data.font);
		data.inputHintText.setCharacterSize(24);
		data.inputHintText.setFillColor(sf::Color::White);	

		switch (game.gameDifficulty)
		{
		case GameDifficulty::Easy:
		{
			data.diffName = "Easy";
			break;
		}
		case GameDifficulty::Normal:
		{
			data.diffName = "Normal";
			break;
		}
		case GameDifficulty::Hard:
		{
			data.diffName = "Hard";
			break;
		}
		case GameDifficulty::VeryHard:
		{
			data.diffName = "VeryHard";
			break;
		}
		case GameDifficulty::Nightmare:
		{
			data.diffName = "Nightmare";
			break;
		}
		default:
			assert(false);
			break;
		}

		data.inputHintText.setString("Difficulty: " + data.diffName);
		data.inputHintText.setOrigin(GetTextOrigin(data.inputHintText, { 1.f, 0.f }));

		data.eatAppleSound.setBuffer(data.eatAppleSoundBuffer);
		data.gameOverSound.setBuffer(data.gameOverSoundBuffer);
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
	void HandeInput(PlayingStateData& data)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			data.snake.direction = SnakeDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			data.snake.direction = SnakeDirection::Up;
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
		MoveSnake(data.snake, deltaTime);

		if (CheckSpriteIntersection(*data.snake.head, data.apple.sprite)) 
		{
			data.eatAppleSound.play();

			GrowSnake(data.snake);

		
			data.numEatenApples++;

			switch (game.gameDifficulty)
			{
			case GameDifficulty::Easy:
			{
				data.score = data.numEatenApples * 2;
				break;
			}
			case GameDifficulty::Normal:
			{
				data.score = data.numEatenApples * 4;
				break;
			}
			case GameDifficulty::Hard:
			{
				data.score = data.numEatenApples * 6;
				break;
			}
			case GameDifficulty::VeryHard:
			{
				data.score = data.numEatenApples * 8;
				break;
			}
			case GameDifficulty::Nightmare:
			{
				data.score = data.numEatenApples * 10;
				break;
			}
			default:
				assert(false);
				break;
			}
			

			SetSpriteRandomPosition(data.apple.sprite, data.inerBoard.getGlobalBounds(), data.snake.body);

			data.snake.speed += ACCELERATION;
			
		}
		

		if (!HasSnakeCollisionWithRect(data.snake, data.inerBoard.getGlobalBounds()) || CheckSnakeCollisionWithHimself(data.snake))
		{
			data.gameOverSound.play();
			
			game.recordsTable[PLAYER_NAME] = std::max(game.recordsTable[PLAYER_NAME], data.score);
			PushGameState(game, GameStateType::GameOver, false);
		}

		data.appleText.setString("Apples eaten: " + std::to_string(data.numEatenApples));
		data.scoreText.setString("Score: " + std::to_string(data.score));
	}

	

	void DrawPlayingState(PlayingStateData& data, Game& game, sf::RenderWindow& window)
	{
		window.draw(data.header);
		window.draw(data.outBoard);
		window.draw(data.inerBoard);		

		DrawSnake(data.snake, window);
		DrawApple(data.apple, window);

		data.appleText.setOrigin(GetTextOrigin(data.scoreText, { 0.f, 0.f }));
		data.appleText.setPosition(10.f, 5.f);
		window.draw(data.appleText);

		data.scoreText.setOrigin(GetTextOrigin(data.scoreText, { 0.f, 0.f }));
		data.scoreText.setPosition(250.f, 5.f);
		window.draw(data.scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		data.inputHintText.setPosition(viewSize.x - 10.f, 5.f);
		window.draw(data.inputHintText);
	}
	void ShutdownPlayingState(PlayingStateData& data, Game& game)
	{
	}
}

#include "GameOver.h"
#include <assert.h>
#include "Game.h"



namespace SnakeGame
{
	void InitGameOverState(GameOverData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		data.timeSinceGameOver = 0.f;

		data.gameOver.setFont(data.font);
		data.gameOver.setCharacterSize(56);

		data.info.setFont(data.font);
		data.info.setCharacterSize(30);
		data.info.setFillColor(sf::Color::White);
		data.info.setString("Press Space to restart game");
		data.info.setOrigin(GetTextOrigin(data.info, { 0.5f, 0.5f }));

	}
	void HandleGameOverWindowEvent(GameOverData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				SwitchGameState(game, GameStateType::Playing);
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				PushGameState(game, GameStateType::Pause, true);
			}
		}
	}
	bool isGameWin = false;
	void GameWin(GameOverData& data)
	{
		isGameWin = true;
	}
	void GameLost(GameOverData& data)
	{
		isGameWin = false;
	}
	void UpdateGameOver(GameOverData& data, Game& game, float deltaTime)
	{
		data.timeSinceGameOver += deltaTime;
		//PushGameState(game, GameStateType::RecordsTable, false);			
	}
	void DrawGameOver(GameOverData& data, Game& game, sf::RenderWindow& window)
	{
		if (isGameWin)
		{
			data.gameOver.setString("You are win!!!");
			sf::Color gameWinTextColor = (int)data.timeSinceGameOver % 2 ? sf::Color::Green : sf::Color::White;
			data.gameOver.setFillColor(gameWinTextColor);
		}
		else
		{
			data.gameOver.setString("You are lost!!!");
			sf::Color gameLostTextColor = (int)data.timeSinceGameOver % 2 ? sf::Color::Red : sf::Color::White;
			data.gameOver.setFillColor(gameLostTextColor);
		}
		sf::Vector2f viewSize = window.getView().getSize();

		data.gameOver.setOrigin(GetTextOrigin(data.gameOver, { 0.5f, 0.5f }));
		data.gameOver.setPosition(viewSize.x / 2.f, viewSize.y / 2.f - 50.f);
		window.draw(data.gameOver);

		data.info.setPosition(viewSize.x / 2.f, viewSize.y / 2.f + 250.f);
		window.draw(data.info);
	}
	void ShutdownGameOver(GameOverData& data, Game& game)
	{

	}
}

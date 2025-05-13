#include "GameOver.h"
#include <assert.h>
#include "Game.h"
#include <assert.h>
#include <sstream>
#include "Math.h"



namespace SnakeGame
{
	const char* PLAYER_NAME = "Player";
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

		data.recordsTableTexts.reserve(MAX_RECORDS_TABLE_SIZE);

		std::multimap<int, std::string> sortedRecordsTable;
		int snakeScores = game.recordsTable[PLAYER_NAME];
		for (const auto& item : game.recordsTable)
		{
			sortedRecordsTable.insert(std::make_pair(item.second, item.first));
		}

		bool isSnakeInTable = false;
		auto it = sortedRecordsTable.rbegin();
		for (int i = 0; i < MAX_RECORDS_TABLE_SIZE && it != sortedRecordsTable.rend(); ++i, ++it) 
		{
			data.recordsTableTexts.emplace_back(); 
			sf::Text& text = data.recordsTableTexts.back();

			
			std::stringstream sstream;
			sstream << i + 1 << ". " << it->second << ": " << it->first;
			text.setString(sstream.str());
			text.setFont(data.font);
			text.setCharacterSize(24);
			if (it->second == PLAYER_NAME)
			{
				text.setFillColor(sf::Color::Green);
				isSnakeInTable = true;
			}
			else
			{
				text.setFillColor(sf::Color::White);
			}
		}

		// If snake is not in table, replace last element with him
		if (!isSnakeInTable)
		{
			sf::Text& text = data.recordsTableTexts.back();
			std::stringstream sstream;
			sstream << MAX_RECORDS_TABLE_SIZE << ". " << PLAYER_NAME << ": " << snakeScores;
			text.setString(sstream.str());
			text.setFillColor(sf::Color::Green);
		}

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

		data.gameOver.setOrigin(GetTextOrigin(data.gameOver, { 0.5f, 1.f }));
		data.gameOver.setPosition(viewSize.x / 2.f, viewSize.y / 2 - 50.f);
		window.draw(data.gameOver);

		// We need to create new vector here as DrawItemsList needs vector of pointers
		std::vector<sf::Text*> textsList;
		textsList.reserve(data.recordsTableTexts.size());
		for (auto& text : data.recordsTableTexts)
		{
			textsList.push_back(&text);
		}

		sf::Vector2f tablePosition = { viewSize.x / 2, viewSize.y / 2.f };
		DrawTextList(window, textsList, 10.f, Orientation::Vertical, Alignment::Min, tablePosition, { 0.5f, 0.f });

		data.info.setOrigin(GetTextOrigin(data.info, { 0.5f, 1.f }));
		data.info.setPosition(viewSize.x / 2.f, viewSize.y - 50.f);
		window.draw(data.info);
	}
	void ShutdownGameOver(GameOverData& data, Game& game)
	{

	}
}

#include "RecordsTable.h"
#include <assert.h>

namespace SnakeGame
{
	void GenerateFakeRecordsTable(Game& game)
	{
		int MaxScore = 100;
		if ((std::uint8_t)game.gameMode & (std::uint8_t)GameSettingsBits::infiniteApple)
		{
			MaxScore = 100;
		}
		else
		{
			MaxScore = game.numEatenApples;
		}
		game.recordsTable =
		{
			{"Kate", GetRandomNumber(0, MaxScore)},
			{"Max", GetRandomNumber(0, MaxScore)},
			{"Andru", GetRandomNumber(0, MaxScore)},
			{"Sara", GetRandomNumber(0, MaxScore)},
			{"You", 0},
		};
	}

	void InitRecordsTable(RecordsTableData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		data.records.setFont(data.font);
		data.records.setCharacterSize(30);
		data.records.setFillColor(sf::Color::White);
		GenerateFakeRecordsTable(game);
	}

	void HandleRecordsTableWindowEvent(RecordsTableData& data, Game& game, sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PopGameState(game);
			}
		}
	}

	void UpdateRecordsTable(RecordsTableData& data, Game& game, float deltaTime)
	{
		data.records.setString("Records: \n");
		for (const auto& item : game.recordsTable)
		{
			data.records.setString(data.records.getString() + "\n" + item.first + ": " + std::to_string(item.second));
		}
		game.recordsTable["You"] = std::max(game.recordsTable["You"], game.numEatenApples);
		data.records.setOrigin(GetTextOrigin(data.records, { 0.5f, 0.5f }));
	}

	void DrawRecordsTable(RecordsTableData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();
		data.records.setPosition(viewSize.x / 2.f, viewSize.y / 2.f);
		window.draw(data.records);
	}

	void ShutdownRecordsTable(RecordsTableData& data, Game& game)
	{
	}
}

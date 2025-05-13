#include "RecordsTable.h"
#include "Math.h"
#include <assert.h>
#include <sstream>

namespace SnakeGame
{
	void InitRecordsTable(RecordsTableData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		data.titleText.setString("RECORDS");
		data.titleText.setFont(data.font);
		data.titleText.setFillColor(sf::Color::Red);
		data.titleText.setCharacterSize(48);

		data.tableTexts.reserve(MAX_RECORDS_TABLE_SIZE);

		std::map<int, std::string> sortedRecordsTable;
		for (const auto& item : game.recordsTable)
		{
			sortedRecordsTable[item.second] = item.first;
		}

		auto it = sortedRecordsTable.rbegin();
		for (int i = 0; i < MAX_RECORDS_TABLE_SIZE && it != sortedRecordsTable.rend(); ++i, ++it) 
		{
			data.tableTexts.emplace_back(); 
			sf::Text& text = data.tableTexts.back();

	
			std::stringstream sstream;
			sstream << i + 1 << ". " << it->second << ": " << it->first;
			text.setString(sstream.str());
			text.setFont(data.font);
			text.setFillColor(sf::Color::White);
			text.setCharacterSize(24);
		}

		data.hintText.setString("Press ESC to return back to main menu");
		data.hintText.setFont(data.font);
		data.hintText.setFillColor(sf::Color::White);
		data.hintText.setCharacterSize(24);
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
		
	}
	
	void DrawRecordsTable(RecordsTableData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		data.titleText.setOrigin(GetTextOrigin(data.titleText, { 0.5f,0.f }));
		data.titleText.setPosition(viewSize.x / 2.f, 50.f);
		window.draw(data.titleText);

		std::vector<sf::Text*> textsList;
		textsList.reserve(data.tableTexts.size());
		for (auto& text : data.tableTexts)
		{
			textsList.push_back(&text);
		}

		sf::Vector2f tablePosition = { data.titleText.getGlobalBounds().left, viewSize.y / 2.f };
		DrawTextList(window, textsList, 10.f, Orientation::Vertical, Alignment::Min, tablePosition, { 0.f, 0.f });

		data.hintText.setOrigin(GetTextOrigin(data.hintText, { 0.5f, 1.f }));
		data.hintText.setPosition(viewSize.x / 2.f, viewSize.y - 50.f);
		window.draw(data.hintText);
	}

	void ShutdownRecordsTable(RecordsTableData& data, Game& game)
	{
	}
}

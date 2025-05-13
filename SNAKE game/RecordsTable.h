#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "PlayingState.h"

namespace SnakeGame
{
	struct Game;

	struct RecordsTableData
	{
		//Resources
		sf::Font font;

		sf::Text titleText;
		std::vector<sf::Text> tableTexts;
		sf::Text hintText;
	};
	void InitRecordsTable(RecordsTableData& data, Game& game);
	void HandleRecordsTableWindowEvent(RecordsTableData& data, Game& game, sf::Event& event);
	void UpdateRecordsTable(RecordsTableData& data, Game& game, float deltaTime);
	
	void DrawRecordsTable(RecordsTableData& data, Game& game, sf::RenderWindow& window);
	void ShutdownRecordsTable(RecordsTableData& data, Game& game);	
}

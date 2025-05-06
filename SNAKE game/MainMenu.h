#pragma once
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include "Math.h"


namespace SnakeGame
{
	struct Game;

	struct MainMenuData
	{
		sf::Font font;

		MenuItem startGameItem;
		MenuItem optionsItem;
		MenuItem optionsInfiniteApplesItem;
		MenuItem optionsWithAccelerationItem;
		MenuItem recordsTable;
		MenuItem exitGameItem;
		MenuItem yesItem;
		MenuItem noItem;
		Menu menu;
	};

	void InitMainMenu(MainMenuData& data, Game&game);
	void HandleMainMenuWindowEvent(MainMenuData& data, Game& game, const sf::Event& event);
	void UpdateMainMenu(MainMenuData& data, Game& game, float deltaTime);
	void DrawMainMenu(MainMenuData& data, Game& game, sf::RenderWindow& window);
	void ShutdownMainMenu(MainMenuData& data, Game& game);
}



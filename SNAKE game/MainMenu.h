#pragma once
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include "Math.h"
#include "Game.h"



namespace SnakeGame
{
	struct Game;

	struct MainMenuData
	{
		sf::Font font;

		MenuItem startGameItem;
		MenuItem optionsItem;
		MenuItem easyItem;
		MenuItem normalItem;
		MenuItem hardItem;
		MenuItem veryHardItem;
		MenuItem nightmareItem;
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



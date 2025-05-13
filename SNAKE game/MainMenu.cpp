#include "MainMenu.h"
#include <assert.h>



namespace SnakeGame
{
	void InitMainMenu(MainMenuData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		data.menu.rootItem.hintText.setString("Snake Game");
		data.menu.rootItem.hintText.setFont(data.font);
		data.menu.rootItem.hintText.setCharacterSize(48);
		data.menu.rootItem.hintText.setFillColor(sf::Color::Red);
		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 10.f;
		data.menu.rootItem.children.push_back(&data.startGameItem);
		data.menu.rootItem.children.push_back(&data.optionsItem);
		data.menu.rootItem.children.push_back(&data.recordsTable);
		data.menu.rootItem.children.push_back(&data.exitGameItem);

		data.startGameItem.text.setString("Start Game");
		data.startGameItem.text.setFont(data.font);
		data.startGameItem.text.setCharacterSize(24);

		data.optionsItem.text.setString("Game Difficulty");
		data.optionsItem.text.setFont(data.font);
		data.optionsItem.text.setCharacterSize(24);
		data.optionsItem.hintText.setString("Game Difficulty");
		data.optionsItem.hintText.setFont(data.font);
		data.optionsItem.hintText.setCharacterSize(48);
		data.optionsItem.hintText.setFillColor(sf::Color::Red);
		data.optionsItem.childrenOrientation = Orientation::Vertical;
		data.optionsItem.childrenAlignment = Alignment::Middle;
		data.optionsItem.childrenSpacing = 10.f;
		data.optionsItem.children.push_back(&data.easyItem);
		data.optionsItem.children.push_back(&data.normalItem);
		data.optionsItem.children.push_back(&data.hardItem);
		data.optionsItem.children.push_back(&data.veryHardItem);
		data.optionsItem.children.push_back(&data.nightmareItem);

		data.easyItem.text.setString("Easy");
		data.easyItem.text.setFont(data.font);
		data.easyItem.text.setCharacterSize(24);

		data.normalItem.text.setString("Normal");
		data.normalItem.text.setFont(data.font);
		data.normalItem.text.setCharacterSize(24);

		data.hardItem.text.setString("Hard");
		data.hardItem.text.setFont(data.font);
		data.hardItem.text.setCharacterSize(24);

		data.veryHardItem.text.setString("Very Hard");
		data.veryHardItem.text.setFont(data.font);
		data.veryHardItem.text.setCharacterSize(24);

		data.nightmareItem.text.setString("Nightmare");
		data.nightmareItem.text.setFont(data.font);
		data.nightmareItem.text.setCharacterSize(24);

		data.recordsTable.text.setString("Records Table");
		data.recordsTable.text.setFont(data.font);
		data.recordsTable.text.setCharacterSize(24);

		data.exitGameItem.text.setString("Exit Game");
		data.exitGameItem.text.setFont(data.font);
		data.exitGameItem.text.setCharacterSize(24);
		data.exitGameItem.hintText.setString("Are you sure?");
		data.exitGameItem.hintText.setFont(data.font);
		data.exitGameItem.hintText.setCharacterSize(48);
		data.exitGameItem.hintText.setFillColor(sf::Color::Red);
		data.exitGameItem.childrenOrientation = Orientation::Horizontal;
		data.exitGameItem.childrenAlignment = Alignment::Middle;
		data.exitGameItem.childrenSpacing = 10.f;
		data.exitGameItem.children.push_back(&data.yesItem);
		data.exitGameItem.children.push_back(&data.noItem);

		data.yesItem.text.setString("Yes");
		data.yesItem.text.setFont(data.font);
		data.yesItem.text.setCharacterSize(24);

		data.noItem.text.setString("No");
		data.noItem.text.setFont(data.font);
		data.noItem.text.setCharacterSize(24);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.startGameItem);
	}

	void HandleMainMenuWindowEvent(MainMenuData& data, Game& game, const sf::Event& event)
	{
		if (!data.menu.selectedItem)
		{
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				CollapseSelectedItem(data.menu);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (data.menu.selectedItem == &data.startGameItem)
				{
					SwitchGameState(game, GameStateType::Playing);
				}
				else if (data.menu.selectedItem == &data.optionsItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.easyItem)
				{
					game.gameDifficulty = GameDifficulty::Easy;
				}
				else if (data.menu.selectedItem == &data.normalItem)
				{
					game.gameDifficulty = GameDifficulty::Normal;
				}
				else if (data.menu.selectedItem == &data.hardItem)
				{
					game.gameDifficulty = GameDifficulty::Hard;
				}
				else if (data.menu.selectedItem == &data.veryHardItem)
				{
					game.gameDifficulty = GameDifficulty::VeryHard;
				}
				else if (data.menu.selectedItem == &data.nightmareItem)
				{
					game.gameDifficulty = GameDifficulty::Nightmare;
				}
				else if (data.menu.selectedItem == &data.recordsTable)
				{
					PushGameState(game, GameStateType::RecordsTable, true);
				}
				else if (data.menu.selectedItem == &data.exitGameItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.yesItem)
				{
					SwitchGameState(game, GameStateType::None);
				}
				else if (data.menu.selectedItem == &data.noItem)
				{
					CollapseSelectedItem(data.menu);
				}
				else
				{
					ExpandSelectedItem(data.menu);
				}
			}

			Orientation orientation = data.menu.selectedItem->parent->childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::W ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::A)
			{
				SelectPreviousMenuItem(data.menu);
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::S ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::D)
			{
				SelectNextMenuItem(data.menu);
			}
		}
	}
	void UpdateMainMenu(MainMenuData& data, Game& game, float deltaTime)
	{
		
	}
	void DrawMainMenu(MainMenuData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		DrawMenu(data.menu, window, viewSize / 2.f, { 0.5f, 0.f });
	}
	void ShutdownMainMenu(MainMenuData& data, Game& game)
	{

	}

}

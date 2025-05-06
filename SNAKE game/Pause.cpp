#include "Pause.h"
#include <assert.h>
#include "Game.h"

namespace SnakeGame
{
	void InitPause(PauseData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		data.modalkaBackground.setSize({ MODALKA_WIDTH, MODALKA_HIGHT });
		data.modalkaBackground.setOrigin({ MODALKA_WIDTH / 2,MODALKA_HIGHT / 2 });
		data.modalkaBackground.setFillColor(sf::Color::White);

		data.text.setFont(data.font);
		data.text.setCharacterSize(24);
		data.text.setFillColor(sf::Color::Black);
		data.text.setString("PAUSE\nEscape - Continue\nEnter - Exit to the main menu");
		data.text.setOrigin(GetTextOrigin(data.text, { 0.5f, 0.5f }));

	}
	void HandlePauseWindowEvent(PauseData& data, Game& game, sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PopGameState(game);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				SwitchGameState(game, GameStateType::MainMenu);
			}
		}
	}
	void UpdatePause(PauseData& data, Game& game, float deltaTime)
	{
	}
	void DrawPause(PauseData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();
		data.modalkaBackground.setPosition(viewSize.x / 2.f, viewSize.y / 2.f);
		window.draw(data.modalkaBackground);

		data.text.setPosition(viewSize.x / 2.f, viewSize.y / 2.f);
		window.draw(data.text);
	}
	void ShutdownPause(PauseData& data, Game& game)
	{
	}
}
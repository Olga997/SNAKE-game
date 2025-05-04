#pragma once
#include "SFML/Graphics.hpp"

namespace ApplesGame
{
	struct Game;
	struct GameStatePauseData
	{
		//Resources
		sf::Font font;

		sf::RectangleShape modalkaBackground;
		sf::Text text;
	};
	void InitGameStatePause(GameStatePauseData& data, Game& game);
	void HandleGameStatePauseWindowEvent(GameStatePauseData& data, Game& game, sf::Event& event);
	void UpdateGameStatePause(GameStatePauseData& data, Game& game, float deltaTime);
	void DrawGameStatePause(GameStatePauseData& data, Game& game, sf::RenderWindow& window);
	void ShutdownGameStatePause(GameStatePauseData& data, Game& game);
}
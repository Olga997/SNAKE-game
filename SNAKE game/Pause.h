#pragma once
#include "SFML/Graphics.hpp"

namespace SnakeGame
{
	struct Game;
	struct PauseData
	{
		//Resources
		sf::Font font;

		sf::RectangleShape modalkaBackground;
		sf::Text text;
	};
	void InitPause(PauseData& data, Game& game);
	void HandlePauseWindowEvent(PauseData& data, Game& game, sf::Event& event);
	void UpdatePause(PauseData& data, Game& game, float deltaTime);
	void DrawPause(PauseData& data, Game& game, sf::RenderWindow& window);
	void ShutdownPause(PauseData& data, Game& game);
}
#pragma once
#include "SFML/Graphics.hpp"


namespace SnakeGame
{
	struct Game;
	struct GameOverData
	{
		//Resources
		sf::Font font;

		float timeSinceGameOver = 0.f;

		//UI data
		sf::Text score;

		sf::Text records;
		sf::Text gameOver;
		sf::Text info;
		std::vector<sf::Text> recordsTableTexts;
	};

	void InitGameOverState(GameOverData& data, Game& game);
	void HandleGameOverWindowEvent(GameOverData& data, Game& game, const sf::Event& event);
	void GameWin(GameOverData& data);
	void GameLost(GameOverData& data);
	void UpdateGameOver(GameOverData& data, Game& game, float deltaTime);
	void DrawGameOver(GameOverData& data, Game& game, sf::RenderWindow& window);
	void ShutdownGameOver(GameOverData& data, Game& game);
}


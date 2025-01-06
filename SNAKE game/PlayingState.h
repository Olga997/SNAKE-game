#pragma once
#include "SFML/Graphics.hpp"
#include "Snake.h"
#include "GameBoard.h"


namespace SnakeGame
{
	struct Game;
	struct PlayingStateData
	{
		Snake snake;
		GameBoard board;
	};

	void InitPlayingState(PlayingStateData& data, Game& game);
	void HandlePlayingStateWindowEvent(PlayingStateData& data, Game& game, const sf::Event& event);
	void HandeInput(PlayingStateData& data);
	void UpdatePlayingStateData(PlayingStateData& data, Game& game, float deltaTime);
	void DrawPlayingState(PlayingStateData&data, Game& game, sf::RenderWindow& window);
	void ShutdownPlayingState(PlayingStateData& data, Game& game);
}

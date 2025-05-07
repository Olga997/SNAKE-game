#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Snake.h"
#include "GameBoard.h"
#include "Game.h"
#include "Rock.h"
#include "Apple.h"


namespace SnakeGame
{
	struct Game;
	struct PlayingStateData
	{
		// Resources
		sf::Texture appleTexture;
		sf::Texture rockTexture;
		sf::Font font;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;

		// Game data
		Snake snake;
		GameBoard board;
		Apple apple;
		std::vector<sf::Sprite> rocks;
		int numEatenApples = 0;

		//std::vector<Rock> rocks;

		// UI data
		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;

		// Sounds
		sf::Sound eatAppleSound;
		sf::Sound gameOverSound;
	};

	void InitPlayingState(PlayingStateData& data, Game& game);
	void HandlePlayingStateWindowEvent(PlayingStateData& data, Game& game, const sf::Event& event);
	void HandeInput(PlayingStateData& data);
	void UpdatePlayingState(PlayingStateData& data, Game& game, float deltaTime);
	void DrawPlayingState(PlayingStateData&data, Game& game, sf::RenderWindow& window);
	void ShutdownPlayingState(PlayingStateData& data, Game& game);
}

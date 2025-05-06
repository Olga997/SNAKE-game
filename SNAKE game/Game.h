#pragma once
#include<SFML/Graphics.hpp>
#include "Apple.h"
#include "Snake.h"
#include "Settings.h"
#include <unordered_map>


namespace SnakeGame
{
	enum class GameSettingsBits : std::uint8_t
	{
		infiniteApple = 1 << 0,
		acceleratePlayer = 1 << 1,

		Default = infiniteApple | acceleratePlayer,
		Empty = 0
	};

	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		Pause,
		RecordsTable,
	};

	struct GameState
	{
		GameStateType type = GameStateType::None;
		void* data = nullptr;
		bool isExclusivelyVisible = false;
	};
	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Swith
	};

	struct Game
	{
		std::vector<GameState> gameStateStack;
		GameStateChangeType gameStateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		int numEatenApples = 0;
		bool pendingGameStateIsExclusivelyVisible = false;

		GameSettingsBits gameMode = GameSettingsBits::Default;
		std::map<std::string, int> recordsTable;
	};

	void InitGame(Game& game);
	void HandleWindowEvents(Game& game, sf::RenderWindow& window);
	bool UpdateGame(Game& game, float deltaTime);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void ShutdownGame(Game& game);

	void PushGameState(Game& game, GameStateType stateType, bool isExlusivelyVisible);
	void PopGameState(Game& game);
	void SwitchGameState(Game& game, GameStateType newState);

	void InitGameState(Game& game, GameState& state);
	void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event);
	void UpdateGameState(Game& game, GameState& state, float deltaTime);
	void DrawGameState(Game& game, GameState& state, sf::RenderWindow& window);
	void ShutdownGameState(Game& game, GameState& state);
}
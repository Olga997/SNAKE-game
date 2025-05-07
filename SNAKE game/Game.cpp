#include <assert.h>
#include <algorithm>
#include "PlayingState.h"
#include "GameOver.h"
#include "Pause.h"
#include "MainMenu.h"
#include "RecordsTable.h"

namespace SnakeGame
{
	void InitGame(Game& game)
	{
		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
		SwitchGameState(game, GameStateType::MainMenu);
	}
	void HandleWindowEvents(Game& game, sf::RenderWindow& window)
	{
		//Read event
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window if close button or Escape key pressed
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
			if (game.gameStateStack.size() > 0)
			{
				HandleWindowEventGameState(game, game.gameStateStack.back(), event);
			}
		}
	}
	bool UpdateGame(Game& game, float deltaTime)
	{
		if (game.gameStateChangeType == GameStateChangeType::Swith)
		{
			while (game.gameStateStack.size() > 0)
			{
				ShutdownGameState(game, game.gameStateStack.back());
				game.gameStateStack.pop_back();
			}
		}
		else if (game.gameStateChangeType == GameStateChangeType::Pop)
		{
			if (game.gameStateStack.size() > 0)
			{
				ShutdownGameState(game, game.gameStateStack.back());
				game.gameStateStack.pop_back();
			}
		}
		if (game.pendingGameStateType != GameStateType::None)
		{
			game.gameStateStack.push_back({ game.pendingGameStateType,nullptr,game.pendingGameStateIsExclusivelyVisible });
			InitGameState(game, game.gameStateStack.back());
		}
		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;

		if (game.gameStateStack.size() > 0)
		{
			UpdateGameState(game, game.gameStateStack.back(), deltaTime);
			return true;
		}
		return false;
	}
	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		if (game.gameStateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = game.gameStateStack.rbegin(); it != game.gameStateStack.rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->isExclusivelyVisible)
				{
					break;
				}
			}
			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				DrawGameState(game, **it, window);
			}
		}
	}
	void ShutdownGame(Game& game)
	{
		while (game.gameStateStack.size() > 0)
		{
			ShutdownGameState(game, game.gameStateStack.back());
			game.gameStateStack.pop_back();
		}
		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
	}

	void PushGameState(Game& game, GameStateType stateType, bool isExlusivelyVisible)
	{
		game.pendingGameStateType = stateType;
		game.pendingGameStateIsExclusivelyVisible = isExlusivelyVisible;
		game.gameStateChangeType = GameStateChangeType::Push;
	}
	void PopGameState(Game& game)
	{
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
		game.gameStateChangeType = GameStateChangeType::Pop;
	}
	void SwitchGameState(Game& game, GameStateType newState)
	{
		game.pendingGameStateType = newState;
		game.pendingGameStateIsExclusivelyVisible = false;
		game.gameStateChangeType = GameStateChangeType::Swith;
	}

	void InitGameState(Game& game, GameState& state)
	{
		switch (state.type)
		{
		case GameStateType::Playing:
		{
			state.data = new PlayingStateData();
			InitPlayingState(*(PlayingStateData*)state.data, game);
			break;
		}
		case GameStateType::GameOver:
		{
			state.data = new GameOverData();
			InitGameOverState(*(GameOverData*)state.data, game);
			break;
		}
		case GameStateType::MainMenu:
		{
			state.data = new MainMenuData();
			InitMainMenu(*(MainMenuData*)state.data, game);
			break;
		}
		case GameStateType::Pause:
		{
			state.data = new PauseData();
			InitPause(*(PauseData*)state.data, game);
			break;
		}
		case GameStateType::RecordsTable:
		{
			state.data = new RecordsTableData();
			InitRecordsTable(*(RecordsTableData*)state.data, game);
			break;
		}

		default:
			assert(false);
			break;
		}
	}
	void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event)
	{
		switch (state.type)
		{
		case GameStateType::Playing:
		{
			HandlePlayingStateWindowEvent(*(PlayingStateData*)state.data, game, event);
			break;
		}
		case GameStateType::GameOver:
		{
			HandleGameOverWindowEvent(*(GameOverData*)state.data, game, event);
			break;
		}
		case GameStateType::MainMenu:
		{
			HandleMainMenuWindowEvent(*(MainMenuData*)state.data, game, event);
			break;
		}
		case GameStateType::Pause:
		{
			HandlePauseWindowEvent(*(PauseData*)state.data, game, event);
			break;
		}
		case GameStateType::RecordsTable:
		{
			HandleRecordsTableWindowEvent(*(RecordsTableData*)state.data, game, event);
			break;
		}
		default:
			assert(false);
			break;
		}
	}
	void UpdateGameState(Game& game, GameState& state, float deltaTime)
	{
		switch (state.type)
		{
		case GameStateType::Playing:
		{
			UpdatePlayingState(*(PlayingStateData*)state.data, game, deltaTime);
			break;
		}
		case GameStateType::GameOver:
		{
			UpdateGameOver(*(GameOverData*)state.data, game, deltaTime);
			break;
		}
		case GameStateType::MainMenu:
		{
			UpdateMainMenu(*(MainMenuData*)state.data, game, deltaTime);
			break;
		}
		case GameStateType::Pause:
		{
			UpdatePause(*(PauseData*)state.data, game, deltaTime);
			break;
		}
		case GameStateType::RecordsTable:
		{
			UpdateRecordsTable(*(RecordsTableData*)state.data, game, deltaTime);
			break;
		}
		default:
			assert(false);
			break;
		}
	}
	void DrawGameState(Game& game, GameState& state, sf::RenderWindow& window)
	{
		switch (state.type)
		{
		case GameStateType::Playing:
		{
			DrawPlayingState(*(PlayingStateData*)state.data, game, window);
			break;
		}
		case GameStateType::GameOver:
		{
			DrawGameOver(*(GameOverData*)state.data, game, window);
			break;
		}
		case GameStateType::MainMenu:
		{
			DrawMainMenu(*(MainMenuData*)state.data, game, window);
			break;
		}
		case GameStateType::Pause:
		{
			DrawPause(*(PauseData*)state.data, game, window);
			break;
		}
		case GameStateType::RecordsTable:
		{
			DrawRecordsTable(*(RecordsTableData*)state.data, game, window);
			break;
		}
		default:
			assert(false);
			break;
		}
	}
	void ShutdownGameState(Game& game, GameState& state)
	{
		switch (state.type)
		{
		case GameStateType::Playing:
		{
			ShutdownPlayingState(*(PlayingStateData*)state.data, game);
			delete (PlayingStateData*)state.data;
			break;
		}
		case GameStateType::GameOver:
		{
			ShutdownGameOver(*(GameOverData*)state.data, game);
			delete (GameOverData*)state.data;
			break;
		}
		case GameStateType::MainMenu:
		{
			ShutdownMainMenu(*(MainMenuData*)state.data, game);
			delete (MainMenuData*)state.data;
			break;
		}
		case GameStateType::Pause:
		{
			ShutdownPause(*(PauseData*)state.data, game);
			delete (PauseData*)state.data;
			break;
		}
		case GameStateType::RecordsTable:
		{
			ShutdownRecordsTable(*(RecordsTableData*)state.data, game);
			delete (RecordsTableData*)state.data;
			break;
		}
		default:
			assert(false);
			break;
		}
	}
}

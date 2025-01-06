#include "Game.h"
#include <cassert>

namespace SnakeGame
{
	void InitGame(Game& game)
	{
		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
		SwitchGameState(game, GameStateType::Playing);

	}
	void HandeleWindowEvents(Game& game, sf::RenderWindow& window)
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
	void ShutDownGame(Game& game)
	{
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
		/*case GameStateType::GameOver:
		{
			state.data = new GameStateGameOverData();
			InitGameOverState(*(GameStateGameOverData*)state.data, game);
			break;
		}
		case GameStateType::MainMenu:
		{
			state.data = new GameStateMainMenuData();
			InitGameStateMainMenu(*(GameStateMainMenuData*)state.data, game);
			break;
		}
		case GameStateType::Pause:
		{
			state.data = new GameStatePauseData();
			InitGameStatePause(*(GameStatePauseData*)state.data, game);
			break;
		}
		case GameStateType::RecordsTable:
		{
			state.data = new GameStateRecordsTableData();
			InitGameStateRecordsTable(*(GameStateRecordsTableData*)state.data, game);
			break;
		}
		*/
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
		/*case GameStateType::GameOver:
		{
			HandleGameStateGameOverWindowEvent(*(GameStateGameOverData*)state.data, game, event);
			break;
		}
		case GameStateType::MainMenu:
		{
			HandleGameStateMainMenuWindowEvent(*(GameStateMainMenuData*)state.data, game, event);
			break;
		}
		case GameStateType::Pause:
		{
			HandleGameStatePauseWindowEvent(*(GameStatePauseData*)state.data, game, event);
			break;
		}*/
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
			UpdatePlayingStateData(*(PlayingStateData*)state.data, game, deltaTime);
			break;
		}
		/*case GameStateType::GameOver:
		{
			UpdateGameStateGameOver(*(GameStateGameOverData*)state.data, game, deltaTime);
			break;
		}
		case GameStateType::MainMenu:
		{
			UpdateGameStateMainMenu(*(GameStateMainMenuData*)state.data, game, deltaTime);
			break;
		}
		case GameStateType::Pause:
		{
			UpdateGameStatePause(*(GameStatePauseData*)state.data, game, deltaTime);
			break;
		}
		case GameStateType::RecordsTable:
		{
			UpdateGameStateRecordsTable(*(GameStateRecordsTableData*)state.data, game, deltaTime);
			break;
		}*/
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
		/*case GameStateType::GameOver:
		{
			DrawGameStateGameOver(*(GameStateGameOverData*)state.data, game, window);
			break;
		}
		case GameStateType::MainMenu:
		{
			DrawGameStateMainMenu(*(GameStateMainMenuData*)state.data, game, window);
			break;
		}
		case GameStateType::Pause:
		{
			DrawGameStatePause(*(GameStatePauseData*)state.data, game, window);
			break;
		}
		case GameStateType::RecordsTable:
		{
			DrawGameStateRecordsTable(*(GameStateRecordsTableData*)state.data, game, window);
			break;
		}*/
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
		/*case GameStateType::GameOver:
		{
			ShutdownGameStateGameOver(*(GameStateGameOverData*)state.data, game);
			delete (GameStateGameOverData*)state.data;
			break;
		}
		case GameStateType::MainMenu:
		{
			ShutdownGameStateMainMenu(*(GameStateMainMenuData*)state.data, game);
			delete (GameStateMainMenuData*)state.data;
			break;
		}
		case GameStateType::Pause:
		{
			ShutdownGameStatePause(*(GameStatePauseData*)state.data, game);
			delete (GameStatePauseData*)state.data;
			break;
		}
		case GameStateType::RecordsTable:
		{
			ShutdownGameStateRecordsTable(*(GameStateRecordsTableData*)state.data, game);
			delete (GameStateRecordsTableData*)state.data;
			break;
		}*/
		default:
			assert(false);
			break;
		}
	}
}

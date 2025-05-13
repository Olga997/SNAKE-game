#pragma once
#include <string>

namespace SnakeGame
{
	const std::string RESOURCES_PATH = "Resources/";

	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEGHT = 600;
	
	constexpr float SNAKE_SIZE = 20.f;
	const unsigned int INITIAL_SNAKE_SIZE = 3;
	constexpr float INITIAL_SPEED = 50.f;
	constexpr float ACCELERATION = 10.f;

	constexpr float APPLE_SIZE = 20.f;

	const int MAX_RECORDS_TABLE_SIZE = 5;
	extern const char* PLAYER_NAME;
}